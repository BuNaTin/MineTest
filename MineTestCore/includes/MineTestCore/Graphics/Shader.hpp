
#pragma once 

#include <string> 

namespace MineTest {

    class Shader {
    public:
        explicit Shader(unsigned int id);
        ~Shader();
    public:
        void use();
    private:
        unsigned int m_id;
    };

    /* extern */Shader* make_shader(const std::string vertexFile, const std::string fragmentFile);

}