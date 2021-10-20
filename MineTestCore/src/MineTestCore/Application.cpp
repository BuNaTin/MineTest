
#include "../includes/MineTestCore/Application.hpp"

#include <../includes/MineTestCore/Window.hpp>
#include <../includes/MineTestCore/Log.hpp>

namespace MineTest {

	int Application::initialization(int w, int h, const char* title) {
        CONSOLE_LOG_INFO("[Application] Start initialization");

		Window::initialization(w, h, title);

        CONSOLE_LOG_INFO("[Application] End initialization");
        
        return 0;
	}

	int Application::start() {
        while (!MineTest::Window::shouldClose())
        {
            /* Render here */
            //glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            MineTest::Window::swapBuffers();

            /* Poll for and process events */
            //glfwPollEvents();

            this->doing();
        }

        return 0;
	}

    int Application::finalization() {
        CONSOLE_LOG_INFO("[Application] Start finalization");

        Window::finalization();

        CONSOLE_LOG_INFO("[Application] End finalization");

        return 0;
    }

}