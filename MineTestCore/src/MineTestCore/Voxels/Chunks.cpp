
#include "../includes/MineTestCore/Voxels/Chunks.hpp"
#include "../includes/MineTestCore/Graphics/Camera.hpp"

#include <MineTestCore/Voxels/Chunk.hpp>
#include <MineTestCore/Voxels/Voxel.hpp>

namespace MineTest {

	Chunks::Chunks(int _w, int _h, int _d):m_w(_w), m_h(_h), m_d(_d), m_volume(_w*_h*_d) {
		m_chunks = new Chunk*[m_volume];

		int index = 0;
		for (int y = 0; y < _h; y++) {
			for (int z = 0; z < _d; z++) {
				for (int x = 0; x < _w; x++, index++) {
					m_chunks[index] = new Chunk(x, y, z);
				}
			}
		}
	}

	Chunks::~Chunks() {
		for (int i = 0; i < m_volume; i++) {
			delete m_chunks[i];
		}
		delete[] m_chunks;
	}

	void Chunks::write(unsigned char* dest) {
		size_t index = 0;
		for (size_t i = 0; i < m_volume; i++) {
			for (size_t j = 0; j < CHUNK_VOL; j++, index++) {
				dest[index] = m_chunks[i]->voxels[j].id;
			}
		}
	}
	void Chunks::read(unsigned char* dest)
	{
		size_t index = 0;
		for (size_t i = 0; i < m_volume; i++) {
			for (size_t j = 0; j < CHUNK_VOL; j++, index++) {
				m_chunks[i]->voxels[j].id = dest[index];
			}
			m_chunks[i]->m_modified = true;
		}
	}
	Voxel* Chunks::get(int x, int y, int z) {
		int cx = x / CHUNK_W;
		int cy = y / CHUNK_H;
		int cz = z / CHUNK_D;
		if (x < 0) cx--;
		if (y < 0) cy--;
		if (z < 0) cz--;
		if (cx < 0 || cy < 0 || cz < 0 || cx >= m_w || cy >= m_h || cz >= m_d)
			return nullptr;
		Chunk* chunk = m_chunks[(cy * m_d + cz) * m_w + cx];
		int lx = x - cx * CHUNK_W;
		int ly = y - cy * CHUNK_H;
		int lz = z - cz * CHUNK_D;
		return &chunk->voxels[(ly * CHUNK_D + lz) * CHUNK_W + lx];
	}
	
	Chunk* Chunks::getChunk(int x, int y, int z) {
		if (x < 0 || y < 0 || z < 0 || x >= m_w || y >= m_h || z >= m_d)
			return nullptr;
		return m_chunks[(y * m_d + z) * m_w + x];
	}

	void Chunks::set(int x, int y, int z, int id) {
		int cx = x / CHUNK_W;
		int cy = y / CHUNK_H;
		int cz = z / CHUNK_D;
		if (x < 0) cx--;
		if (y < 0) cy--;
		if (z < 0) cz--;
		if (cx < 0 || cy < 0 || cz < 0 || cx >= m_w || cy >= m_h || cz >= m_d)
			return;
		Chunk* chunk = m_chunks[(cy * m_d + cz) * m_w + cx];
		int lx = x - cx * CHUNK_W;
		int ly = y - cy * CHUNK_H;
		int lz = z - cz * CHUNK_D;
		chunk->voxels[(ly * CHUNK_D + lz) * CHUNK_W + lx].id = id;
		chunk->m_modified = true;

		if (lx == 0 && (chunk = getChunk(cx - 1, cy, cz))) chunk->m_modified = true;
		if (ly == 0 && (chunk = getChunk(cx, cy - 1, cz))) chunk->m_modified = true;
		if (lz == 0 && (chunk = getChunk(cx, cy, cz - 1))) chunk->m_modified = true;

		if (lx == CHUNK_W - 1 && (chunk = getChunk(cx + 1, cy, cz))) chunk->m_modified = true;
		if (ly == CHUNK_H - 1 && (chunk = getChunk(cx, cy + 1, cz))) chunk->m_modified = true;
		if (lz == CHUNK_D - 1 && (chunk = getChunk(cx, cy, cz + 1))) chunk->m_modified = true;
	}
	Voxel* Chunks::rayCast(glm::vec3 a, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& norm, glm::vec3& iend) {
		float px = a.x;
		float py = a.y;
		float pz = a.z;

		float dx = dir.x;
		float dy = dir.y;
		float dz = dir.z;

		float t = 0.0f;
		int ix = floor(px);
		int iy = floor(py);
		int iz = floor(pz);

		float stepx = (dx > 0.0f) ? 1.0f : -1.0f;
		float stepy = (dy > 0.0f) ? 1.0f : -1.0f;
		float stepz = (dz > 0.0f) ? 1.0f : -1.0f;

		constexpr float infinity = std::numeric_limits<float>::infinity();

		float txDelta = (dx == 0.0f) ? infinity : abs(1.0f / dx);
		float tyDelta = (dy == 0.0f) ? infinity : abs(1.0f / dy);
		float tzDelta = (dz == 0.0f) ? infinity : abs(1.0f / dz);

		float xdist = (stepx > 0) ? (ix + 1 - px) : (px - ix);
		float ydist = (stepy > 0) ? (iy + 1 - py) : (py - iy);
		float zdist = (stepz > 0) ? (iz + 1 - pz) : (pz - iz);

		float txMax = (txDelta < infinity) ? txDelta * xdist : infinity;
		float tyMax = (tyDelta < infinity) ? tyDelta * ydist : infinity;
		float tzMax = (tzDelta < infinity) ? tzDelta * zdist : infinity;

		int steppedIndex = -1;

		while (t <= maxDist) {
			Voxel* voxel = get(ix, iy, iz);
			if (voxel == nullptr || voxel->id) {
				end.x = px + t * dx;
				end.y = py + t * dy;
				end.z = pz + t * dz;

				iend.x = ix;
				iend.y = iy;
				iend.z = iz;

				norm.x = norm.y = norm.z = 0.0f;
				if (steppedIndex == 0) norm.x = -stepx;
				if (steppedIndex == 1) norm.y = -stepy;
				if (steppedIndex == 2) norm.z = -stepz;
				return voxel;
			}
			if (txMax < tyMax) {
				if (txMax < tzMax) {
					ix += stepx;
					t = txMax;
					txMax += txDelta;
					steppedIndex = 0;
				}
				else {
					iz += stepz;
					t = tzMax;
					tzMax += tzDelta;
					steppedIndex = 2;
				}
			}
			else {
				if (tyMax < tzMax) {
					iy += stepy;
					t = tyMax;
					tyMax += tyDelta;
					steppedIndex = 1;
				}
				else {
					iz += stepz;
					t = tzMax;
					tzMax += tzDelta;
					steppedIndex = 2;
				}
			}
		}
		iend.x = ix;
		iend.y = iy;
		iend.z = iz;

		end.x = px + t * dx;
		end.y = py + t * dy;
		end.z = pz + t * dz;
		norm.x = norm.y = norm.z = 0.0f;
		return nullptr;
	}

	bool Chunks::getBlock(Camera* camera, glm::vec3& block, glm::vec3& norm) {
		glm::vec3 end;
		Voxel* vox = this->rayCast(camera->getPosition(), camera->getFront(), 10.0f, end, norm, block);
		return vox != nullptr;
	}

	void Chunks::erazeBlock(const glm::vec3 block) {
		this->set(int(block.x), int(block.y), int(block.z), 0);
	}
	void Chunks::addBlock(const glm::vec3 block, const glm::vec3 norm, const int block_id) {
		this->set(int(block.x) + int(norm.x), int(block.y) + int(norm.y), int(block.z) + int(norm.z), block_id);
	}
}