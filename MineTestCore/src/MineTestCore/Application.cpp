
#include "../includes/MineTestCore/Application.hpp"

#include <MineTestCore/myglad.hpp>

#include <MineTestCore/Window.hpp>
#include <MineTestCore/Events.hpp>
#include <MineTestCore/Log.hpp>
#include <MineTestCore/Graphics/Shader.hpp>


// should delete
#include <GLFW/glfw3.h>
// 

namespace MineTest {

	int Application::initialization(int w, int h, const char* title) {
        CONSOLE_LOG_INFO("[Application] Start initialization");

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
            0.0f, 1.0f, 0.0f
        };

        Shader* shader = load_shader("C:/Users/PC/Documents/projects/MineTest/MineTest/MineTestCore/res/main.glslv", "C:/Users/PC/Documents/projects/MineTest/MineTest/MineTestCore/res/main.glslf");
        if (shader == nullptr) {
            CONSOLE_LOG_ERROR("[Shader] Wrong shader program");
        }

        // should delete
        glad::glClearColor(0, 1, 0, 1);
        //

        while (!MineTest::Window::shouldClose())
        {
            /* Render here */
            glad::glClear();

            /* Poll for and process events */
            Events::poll();

            if (Events::pressed(GLFW_KEY_ESCAPE)) {
                Window::shouldClose(true);
            }
            
            if (Events::jclicked(GLFW_MOUSE_BUTTON_1)) {
                glad::glClearColor(1, 0, 0, 1);
            }

            //glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            MineTest::Window::swapBuffers();

            this->doing();
        }
        return 0;
	}

    int Application::finalization() {
        CONSOLE_LOG_INFO("[Application] Start finalization");

        Events::finalization();
        Window::finalization();

        CONSOLE_LOG_INFO("[Application] End finalization");

        return 0;
    }

}