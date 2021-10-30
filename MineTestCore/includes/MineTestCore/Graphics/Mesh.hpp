
#pragma once

namespace MineTest {

    class Mesh {
    public:
        Mesh(const float buffer[], size_t vertices, const int attrs[]);
        ~Mesh();

        void draw(unsigned int primitive);
        void reload(const float* buffer, size_t vertices);

    private:
        unsigned int m_vertexSize;
        unsigned int m_vao;
        unsigned int m_vbo;
        size_t m_vertices;
    };

}