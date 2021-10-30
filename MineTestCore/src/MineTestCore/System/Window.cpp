
#include <../includes/MineTestCore/System/Window.hpp>

#include <GLFW/glfw3.h>
#include <../includes/MineTestCore/System/Log.hpp>

namespace MineTest {

    GLFWwindow* Window::m_pwindow = nullptr;
    int Window::m_w = 1920;
    int Window::m_h = 1080;


	int Window::initialization(int w, int h, const char title[]) {
        /* Initialize the library */
        if (!glfwInit()) {
            CONSOLE_LOG_CRITICAL("[Window] Could't init GLFW");
            return -1;
        }

        /* Create a windowed mode window and its OpenGL context */
        m_pwindow = glfwCreateWindow(w, h, title, nullptr, nullptr);
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

        CONSOLE_LOG_INFO("[Window] Close window");

        return 0;
    }

    void Window::setCursorMode(int n) {
        glfwSetInputMode(m_pwindow, GLFW_CURSOR, n);
    }

    GLFWwindow* Window::get() {
        return m_pwindow;
    }
    
    void Window::setW(int w) {
        m_w = w;
    }
    
    void Window::setH(int h) {
        m_h = h;
    }

    int Window::getW() {
        return m_w;
    }

    int Window::getH() {
        return m_h;
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(m_pwindow);
    }

    void Window::shouldClose(bool arg) {
        glfwSetWindowShouldClose(m_pwindow, arg);
    }

    void Window::swapBuffers() {
        glfwSwapBuffers(m_pwindow);
    }
}