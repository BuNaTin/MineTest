
#include "../../../includes/MineTestCore/Graphics/Shader.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

#include <MineTestCore/Graphics/myglad.hpp>
#include <MineTestCore/ResourceManager/ResourceManager.hpp>
#include <MineTestCore/System/Log.hpp>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

namespace MineTest {

    Shader::Shader(unsigned int id):m_id(id) {

    }
    Shader::~Shader(){
        glDeleteProgram(m_id);
    }
    void Shader::use() {
        glUseProgram(m_id);
    }

    void Shader::uniformMatrix(const std::string& name, glm::mat4 matrix) {
        GLuint transformLoc = glGetUniformLocation(m_id, name.c_str());
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    
    Shader* make_shader(const std::string& vertexFile, const std::string& fragmentFile) {
        std::string vertexCode = ResourceManager::read_shader(vertexFile);
        std::string fragmentCode = ResourceManager::read_shader(fragmentFile);

        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();

        GLuint vertex, fragment;

        GLint success;
        GLchar infoLog[512];

        // vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            CONSOLE_LOG_ERROR("[Shader] Error in vertex shader");
            CONSOLE_LOG_ERROR(infoLog);
            return nullptr;
        }

        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            CONSOLE_LOG_ERROR("[Shader] Error in fragment shader");
            CONSOLE_LOG_ERROR(infoLog);
            return nullptr;
        }

        // Shader program
        GLuint id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(fragment, 512, nullptr, infoLog);
            CONSOLE_LOG_ERROR("[Shader] Error in fragment shader");
            CONSOLE_LOG_ERROR(infoLog);

            glDeleteShader(vertex);
            glDeleteShader(fragment);
            glDeleteProgram(id);
            return nullptr;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return new Shader(id);
    }
}
