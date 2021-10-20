
#pragma once

struct GLFWwindow;

namespace MineTest {

    class Window {
    public:
        static int initialization(int w, int h, const char title[]);
        static int finalization();
        static bool shouldClose();
        static void swapBuffers();

        Window() = delete;
        ~Window() = delete;
    private:
        static GLFWwindow* m_pwindow;
    };

}
