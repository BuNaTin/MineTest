
#include "../includes/MineTestCore/Voxels/Chunk.hpp"

#include <MineTestCore/Voxels/Voxel.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

namespace MineTest{

	Chunk::Chunk(int _x, int _y, int _z): m_x(_x), m_y(_y), m_z(_z) {
		m_modified = true;
		voxels = new Voxel[CHUNK_VOL];
		// SimpleGeneration
		for (int z = 0; z < CHUNK_D; z++) {
			int real_z = z + this->m_z * CHUNK_D;
			for (int x = 0; x < CHUNK_W; x++) {
				int real_x = x + this->m_x * CHUNK_W;
				float height = glm::perlin(glm::vec3(real_x*0.025f,real_z*0.025f, 0.0f));
				for (int y = 0; y < CHUNK_H; y++) {
					int real_y = y + this->m_y * CHUNK_H;
					int id = real_y <= (height) * 10 + 5;
					if (real_y <= 2)
						id = 2;
					voxels[(y * CHUNK_D + z) * CHUNK_W + x].id = id;
				}
			}
		}
	}

	Chunk::~Chunk() {
		delete[] voxels;
	}

}