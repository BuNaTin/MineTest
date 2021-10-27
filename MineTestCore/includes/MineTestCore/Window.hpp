
#pragma once

struct GLFWwindow;

namespace MineTest {

    class Window {
    public:
        static int initialization(int w, int h, const char title[]);
        static int finalization();
        static bool shouldClose();
        static void shouldClose(bool arg);
        static void swapBuffers();
        static void setCursorMode(int n);

        static GLFWwindow* get();
        

        static void setW(int w);
        static void setH(int h);
        static int getW();
        static int getH();

        Window() = delete;
        ~Window() = delete;
    private:
        static GLFWwindow* m_pwindow;
        static int m_w;
        static int m_h;
    };

}
