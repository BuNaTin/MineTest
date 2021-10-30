
#include "../includes/MineTestCore/Graphics/Mesh.hpp"

#include <MineTestCore/Graphics/myglad.hpp>

namespace MineTest {

	Mesh::Mesh(const float buffer[], size_t vertices, const int attrs[]) : m_vertices(vertices) {
        m_vertexSize = 0;
		for (int i = 0; attrs[i]; i++) {
			m_vertexSize += attrs[i];
		}

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertexSize * vertices, buffer, GL_STATIC_DRAW);

        int offset = 0;
        for (int i = 0; attrs[i]; i++) {
            int size = attrs[i];
            glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, m_vertexSize * sizeof(float), (GLvoid*)(offset * sizeof(float)));
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


    void Mesh::reload(const float* buffer, size_t vertices) {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertexSize * vertices, buffer, GL_STATIC_DRAW);
        m_vertices = vertices;
    }
}