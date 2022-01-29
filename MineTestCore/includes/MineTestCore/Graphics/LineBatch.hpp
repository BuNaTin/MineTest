
#pragma once

namespace MineTest {

	class Mesh;

	class LineBatch {
	public:
		LineBatch(size_t capacity);
		~LineBatch();

		void line(float x1, float y1, float z1, float x2, float y2, float z2,
			float r, float g, float b, float a);
		void box(float x, float y, float z, float w, float h, float d,
			float r, float g, float b, float a); 
		void matchBlock(float x, float y, float z);

		void render();

	private:
		Mesh* m_mesh;
		float* m_buffer;
		size_t m_index;
		size_t m_capacity;
	};

}