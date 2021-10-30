
#pragma once

#include <cstdint>
#include <glm/vec3.hpp>

namespace MineTest {

	class Chunk;
	struct Voxel;

	class Chunks {
	public:
		Chunk** m_chunks;
		size_t m_volume;
		unsigned int m_w, m_h, m_d;

		void write(unsigned char* dest);
		void read(unsigned char* dest);

		Voxel* get(int x, int y, int z);
		Chunk* getChunk(int x, int y, int z);
		void set(int x, int y, int z, int id);
		Voxel* rayCast(glm::vec3 a, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& norm, glm::vec3& iend);

	public:
		Chunks(int _w, int _h, int _d);
		~Chunks();

	};

}