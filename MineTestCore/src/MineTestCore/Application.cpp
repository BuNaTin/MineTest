
#include "../includes/MineTestCore/Application.hpp"

#include <MineTestCore/myglad.hpp>

#include <MineTestCore/Window.hpp>
#include <MineTestCore/Events.hpp>
#include <MineTestCore/Graphics/Camera.hpp>
#include <MineTestCore/Log.hpp>
#include <MineTestCore/ResourceManager/ResourceManager.hpp>
#include <MineTestCore/Graphics/Shader.hpp>
#include <MineTestCore/Graphics/Texture.hpp>
#include <MineTestCore/Graphics/Mesh.hpp>

// test glm
#include <glm/glm.hpp>
#include <glm/ext.hpp>


namespace MineTest {

	int Application::initialization(int w, int h, const char* title, const char* exe_folder) {
        CONSOLE_LOG_INFO("[Application] Start initialization");

        ResourceManager::initialization(exe_folder);


		Window::initialization(w, h, title);
        glad::init();
        Events::initialization();

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

        int attrs[] = {
            3, 2, 0
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
        Mesh* mesh = new Mesh(vertices, 6, attrs);

        
        glad::glClearColor(0.7f, 0.7f, 0.0f, 1.0f);
        //
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Camera* camera = new Camera(glm::vec3(0, 0, 2), glm::radians(70.0f));

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

        float lastTime = glfwGetTime();
        float delta = 0.0f;
        const float speed = 3.0f;

        float camX = 0.0f;
        float camY = 0.0f;

        while (!MineTest::Window::shouldClose())
        {
            float currentTime = glfwGetTime();
            delta = currentTime - lastTime;
            lastTime = currentTime;

            /* Render here */
            glad::glClear();


            this->doing();

            if (Events::pressed(GLFW_KEY_ESCAPE)) {
                Window::shouldClose(true);
            }
            if (Events::jpressed(GLFW_KEY_TAB)) {
                Events::toogleCursor();
            }

            if (Events::pressed(GLFW_KEY_S)) {
                camera->addPosition(-camera->getFront() * delta * speed);
            }
            if (Events::pressed(GLFW_KEY_W)) {
                camera->addPosition(camera->getFront() * delta * speed);
            }
            if (Events::pressed(GLFW_KEY_D)) {
                camera->addPosition(camera->getRight() * delta * speed);
            }
            if (Events::pressed(GLFW_KEY_A)) {
                camera->addPosition(-camera->getRight() * delta * speed);
            }
            if (Events::pressed(GLFW_KEY_SPACE)) {
                //camera->addY(speed * delta);
            }
            if (Events::pressed(GLFW_KEY_LEFT_CONTROL)) {
                //camera->addY(-speed * delta);
            }
            if (Events::m_cursor_locked) {
                camY -= (Events::m_deltaY / Window::getH());
                camX -= (Events::m_deltaX / Window::getW());
                if (camY < -glm::radians(89.0f)) {
                    camY = -glm::radians(89.0f);
                }
                if (camY > glm::radians(89.0f)) {
                    camY = glm::radians(89.0f);
                }

                camera->resetRotation();
                camera->rotate(camY, camX, 0);
            }

            glClear(GL_COLOR_BUFFER_BIT);

            // DRAW VAO
            shader->use();
            shader->uniformMatrix("model", model);
            shader->uniformMatrix("projview", (camera->getProjection())*(camera->getView()));
            texture->bind();
            mesh->draw(GL_TRIANGLES);

            /* Swap front and back buffers */
            MineTest::Window::swapBuffers();

            /* Poll for and process events */
            Events::poll();

        }

        delete mesh;
        delete shader;
        delete texture;
        delete camera;
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