
#pragma once 

#include <string> 
#include <glm/mat4x4.hpp>

namespace MineTest {

    class Shader {
    public:
        explicit Shader(unsigned int id);
        ~Shader();
    public:
        void use();
        void uniformMatrix(const std::string& name, glm::mat4 matrix);
    private:
        unsigned int m_id;
    };

    Shader* make_shader(const std::string& vertexFile, const std::string& fragmentFile);

}