
#include <../includes/MineTestCore/Window.hpp>

#include <GLFW/glfw3.h>
#include <../includes/MineTestCore/Log.hpp>

namespace MineTest {

    GLFWwindow* Window::m_pwindow = nullptr;


	int Window::initialization(int w, int h, const char title[]) {
        /* Initialize the library */
        if (!glfwInit()) {
            CONSOLE_LOG_CRITICAL("[Window] Could't init GLFW");
            return -1;
        }

        /* Create a windowed mode window and its OpenGL context */
        m_pwindow = glfwCreateWindow(640, 480, title, nullptr, nullptr);
        if (!m_pwindow)
        {
            CONSOLE_LOG_CRITICAL("[Window] Could't make window");
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_pwindow);

        CONSOLE_LOG_INFO("[Window] Make window");

        return 0;
	}

    int Window::finalization() {
        glfwTerminate();

        CONSOLE_LOG_INFO("[Window] Terminate window");
        return 0;
    }
    
    bool Window::shouldClose() {
        return glfwWindowShouldClose(m_pwindow);
    }

    void Window::swapBuffers() {
        glfwSwapBuffers(m_pwindow);
    }
}