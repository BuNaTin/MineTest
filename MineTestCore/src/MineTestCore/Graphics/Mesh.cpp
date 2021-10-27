
#include "../includes/MineTestCore/Graphics/Mesh.hpp"

#include <MineTestCore/myglad.hpp>

namespace MineTest {

	Mesh::Mesh(const float buffer[], size_t vertices, const int attrs[]) : m_vertices(vertices) {
		int vertex_size = 0;
		for (int i = 0; attrs[i]; i++) {
			vertex_size += attrs[i];
		}

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);

        int offset = 0;
        for (int i = 0; attrs[i]; i++) {
            int size = attrs[i];
            glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
            glEnableVertexAttribArray(i);
            offset += size;
        }

        glBindVertexArray(0);
	}

    Mesh::~Mesh() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    void Mesh::draw(unsigned int primitive) {
        glBindVertexArray(m_vao);
        glDrawArrays(primitive, 0, m_vertices);
        glBindVertexArray(0);
    }
}