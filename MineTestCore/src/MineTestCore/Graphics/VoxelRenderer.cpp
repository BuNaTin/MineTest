
#include "../includes/MineTestCore/Graphics/VoxelRenderer.hpp"

#include <MineTestCore/Graphics/Mesh.hpp>
#include <MineTestCore/Voxels/Chunk.hpp>
#include <MineTestCore/Voxels/Voxel.hpp>


#define CDIV(X,A) (((X) < 0) ? ((X) / (A) - 1) : ((X) / (A)))
#define LOCAL_NEG(X, SIZE) (((X) < 0) ? ((SIZE)+(X)) : (X))
#define LOCAL(X, SIZE) ((X) >= (SIZE) ? ((X) - (SIZE)) : LOCAL_NEG(X, SIZE))
#define IS_CHUNK(X,Y,Z) (GET_CHUNK(X,Y,Z) != nullptr)
#define GET_CHUNK(X,Y,Z) (chunks[((CDIV(Y, CHUNK_H)+1) * 3 + CDIV(Z, CHUNK_D) + 1) * 3 + CDIV(X, CHUNK_W) + 1])

#define VOXEL(X,Y,Z) (GET_CHUNK(X,Y,Z)->voxels[(LOCAL(Y, CHUNK_H) * CHUNK_D + LOCAL(Z, CHUNK_D)) * CHUNK_W + LOCAL(X, CHUNK_W)])
#define IS_BLOCKED(X,Y,Z) ((!IS_CHUNK(X, Y, Z)) || VOXEL(X, Y, Z).id)

#define VERTEX(INDEX, X,Y,Z, U,V, L) m_buffer[INDEX+0] = (X);\
								  m_buffer[INDEX+1] = (Y);\
								  m_buffer[INDEX+2] = (Z);\
								  m_buffer[INDEX+3] = (U);\
								  m_buffer[INDEX+4] = (V);\
								  m_buffer[INDEX+5] = (L);\
								  INDEX += VERTEX_SIZE;

int chunk_attrs[] = { 3,2,1, 0};

namespace MineTest {

	const size_t VERTEX_SIZE = (3 + 2 + 1);

	VoxelRenderer::VoxelRenderer(size_t capacity) : m_capacity(capacity){
		m_buffer = new float[capacity * VERTEX_SIZE * 6 /* two triangles */];
	}

	VoxelRenderer::~VoxelRenderer() {
		delete[] m_buffer;
	}

	Mesh* VoxelRenderer::render(Chunk* chunk, const Chunk** chunks) {
		size_t index = 0;
		for (int y = 0; y < CHUNK_H; y++) {
			for (int z = 0; z < CHUNK_D; z++) {
				for (int x = 0; x < CHUNK_W; x++) {
					Voxel voxel = chunk->voxels[(y * CHUNK_D + z) * CHUNK_W + x];
					uint8_t id = voxel.id;

					if (id == 0) {
						continue;
					}
					float l;
					float uvsize = 1.0f / 16.0f;
					float u = (id % 16) * uvsize;
					float v = 1 - ((1 + id / 16) * uvsize);
					
					if (!IS_BLOCKED(x, y + 1, z)) {
						l = 1.0f;
						VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
						VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

						VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v, l);
					}
					if (!IS_BLOCKED(x, y - 1, z)) {
						l = 0.75f;
						VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
						VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
						VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v + uvsize, l);

						VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
						VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
						VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
					}

					if (!IS_BLOCKED(x + 1, y, z)) {
						l = 0.95f;
						VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

						VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
						VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u, v, l);
					}
					if (!IS_BLOCKED(x - 1, y, z)) {
						l = 0.85f;
						VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
						VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
						VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

						VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
						VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
						VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
					}

					if (!IS_BLOCKED(x, y, z + 1)) {
						l = 0.9f;
						VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
						VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

						VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
						VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
					}
					if (!IS_BLOCKED(x, y, z - 1)) {
						l = 0.8f;
						VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
						VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

						VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
						VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);
						VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u, v, l);
					}
				}
			}
		}
		return new Mesh(m_buffer, index / VERTEX_SIZE, chunk_attrs);
	}

}