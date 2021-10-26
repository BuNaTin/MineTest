
#include "../includes/MineTestCore/Application.hpp"

#include <MineTestCore/myglad.hpp>

#include <MineTestCore/Window.hpp>
#include <MineTestCore/Events.hpp>
#include <MineTestCore/Log.hpp>
#include <MineTestCore/ResourceManager/ResourceManager.hpp>
#include <MineTestCore/Graphics/Shader.hpp>
#include <MineTestCore/Graphics/Texture.hpp>


namespace MineTest {

	int Application::initialization(int w, int h, const char* title, const char* exe_folder) {
        CONSOLE_LOG_INFO("[Application] Start initialization");

        ResourceManager::initialization(exe_folder);

		Window::initialization(w, h, title);
        Events::initialization();
        glad::init();

        CONSOLE_LOG_INFO("[Application] End initialization");
        
        return 0;
	}

	int Application::start() {

        float vertices[] = {
            // x     y     z     u     v
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f
        };

        // Shader
        Shader* shader = make_shader("main.glslv", "main.glslf");
        if (shader == nullptr) {
            CONSOLE_LOG_ERROR("[Shader] Wrong shader program");
        }
        // Texture
        Texture* texture = make_texture("2.png");
        if (texture == nullptr) {
            CONSOLE_LOG_ERROR("[Texture] Wrong texture");
        }

        // create VAO
        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        


        glBindVertexArray(0);

        
        glad::glClearColor(0.7f, 0.7f, 0.0f, 1.0f);
        //
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        while (!MineTest::Window::shouldClose())
        {
            /* Render here */
            glad::glClear();

            /* Poll for and process events */
            Events::poll();

            this->doing();

            if (Events::pressed(GLFW_KEY_ESCAPE)) {
                Window::shouldClose(true);
            }
            
            if (Events::jclicked(GLFW_MOUSE_BUTTON_1)) {
                glad::glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
            }

            glClear(GL_COLOR_BUFFER_BIT);

            // DRAW VAO
            shader->use();
            texture->bind();

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            /* Swap front and back buffers */
            MineTest::Window::swapBuffers();


        }

        delete shader;
        delete texture;
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);


        return 0;
	}

    int Application::finalization() {
        CONSOLE_LOG_INFO("[Application] Start finalization");

        Events::finalization();
        Window::finalization();
        ResourceManager::finalization();

        CONSOLE_LOG_INFO("[Application] End finalization");

        return 0;
    }

}