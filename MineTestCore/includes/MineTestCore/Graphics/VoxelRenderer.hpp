
#pragma once

#include <MineTestCore/Voxels/Chunk.hpp>

namespace MineTest {

	class Mesh;
	class Chunk;

	class VoxelRenderer {
	public:
		VoxelRenderer(size_t capacity);
		~VoxelRenderer();

		Mesh* render(Chunk* chunk, const Chunk** chunks, bool ambientOcclusion);

	private:

	private:
		size_t m_capacity;
		float* m_buffer;
	};

}