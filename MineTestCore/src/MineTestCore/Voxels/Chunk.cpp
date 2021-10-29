
#include "../includes/MineTestCore/Voxels/Chunk.hpp"

#include <MineTestCore/Voxels/Voxel.hpp>

#include <cmath>

namespace MineTest{

	Chunk::Chunk(int _x, int _y, int _z): m_x(_x), m_y(_y), m_z(_z) {
		voxels = new Voxel[CHUNK_VOL];
		// SimpleGeneration
		for (int y = 0; y < CHUNK_H; y++) {
			for (int z = 0; z < CHUNK_D; z++) {
				for (int x = 0; x < CHUNK_W; x++) {
					int real_x = x + this->m_x * CHUNK_W;
					int real_y = y + this->m_y * CHUNK_H;
					int real_z = z + this->m_z * CHUNK_D;
					uint8_t id = static_cast<uint8_t>(real_y <= (4 * sin(x * 0.6f) + 4));
					if (real_y <= 1) {
						id = 2;
					}
					voxels[(y * CHUNK_D + z) * CHUNK_W + x].id = id;
				}
			}
		}
	}

	Chunk::~Chunk() {
		delete[] voxels;
	}

}