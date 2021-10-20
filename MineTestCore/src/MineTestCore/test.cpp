
#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "../includes/MineTestCore/test.hpp"

int foo() 
{

    /* Loop until the user closes the window */
    while (!Window::shouldClose())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}