
#include "../includes/MineTestCore/Application.hpp"

#include <MineTestCore/myglad.hpp>

#include <MineTestCore/Window.hpp>
#include <MineTestCore/Events.hpp>
#include <MineTestCore/Log.hpp>
#include <MineTestCore/ResourceManager.hpp>
#include <MineTestCore/Graphics/Shader.hpp>

#include <MineTestCore/Graphics/std_image.hpp>



// should delete
// #include <GLFW/glfw3.h>
// 

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
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        Shader* shader = make_shader("main.glslv", "main.glslf");
        if (shader == nullptr) {
            CONSOLE_LOG_ERROR("[Shader] Wrong shader program");
        }

        // create VAO
        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        


        glBindVertexArray(0);

        // should delete
        glad::glClearColor(0, 1, 0, 1);
        //

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
                glad::glClearColor(1, 0, 0, 1);
            }

            glClear(GL_COLOR_BUFFER_BIT);

            // DRAW VAO
            shader->use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

            /* Swap front and back buffers */
            MineTest::Window::swapBuffers();


        }
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