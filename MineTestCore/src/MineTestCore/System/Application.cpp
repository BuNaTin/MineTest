
#include "../includes/MineTestCore/System/Application.hpp"


#include <MineTestCore/System/Window.hpp>
#include <MineTestCore/System/Events.hpp>
#include <MineTestCore/System/Log.hpp>

#include <MineTestCore/ResourceManager/ResourceManager.hpp>

#include <MineTestCore/Graphics/myglad.hpp>
#include <MineTestCore/Graphics/Camera.hpp>
#include <MineTestCore/Graphics/Shader.hpp>
#include <MineTestCore/Graphics/Texture.hpp>
#include <MineTestCore/Graphics/Mesh.hpp>
#include <MineTestCore/Graphics/VoxelRenderer.hpp>
#include <MineTestCore/Graphics/LineBatch.hpp>

#include <MineTestCore/Voxels/Chunk.hpp>
#include <MineTestCore/Voxels/Chunks.hpp>

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

        float cursor[] = {
            // x     y   
            -0.01f, -0.01f,
            0.01f, 0.01f,

            -0.01f, 0.01f,
            0.01f, -0.01f,
        };

        int attrs[] = {
            3, 2, 0
        };

        int cursorAttrs[] = {
            2, 0
        };

        // Shaders
        Shader* shader = make_shader("main.glslv", "main.glslf");
        if (shader == nullptr) {
            CONSOLE_LOG_ERROR("[Shader] Wrong shader program");
        }
        Shader* cursorShader = make_shader("cursor.glslv", "cursor.glslf");
        if (cursorShader == nullptr) {
            CONSOLE_LOG_ERROR("[Shader] Wrong cursorShader program");
        }
        Shader* linesShader = make_shader("lines.glslv", "lines.glslf");
        if (cursorShader == nullptr) {
            CONSOLE_LOG_ERROR("[Shader] Wrong linesShader program");
        }

        // Texture
        Texture* texture = make_texture("2.png");
        if (texture == nullptr) {
            CONSOLE_LOG_ERROR("[Texture] Wrong texture");
        }

        //  load world
        Chunks* chunks = new Chunks(16, 1, 16);
        VoxelRenderer renderer(1024 * 1024 * 8);
        LineBatch* lineBatch = new LineBatch(1024);
        // init meshes
        Mesh** meshes = new Mesh * [chunks->m_volume];
        for (uint32_t i = 0; i < chunks->m_volume; i++) {
            meshes[i] = nullptr;
        }

        // make cursor
        Mesh* cursorMesh = new Mesh(cursor, 4, cursorAttrs);
        
        // gl settings
        glad::glClearColor(0.5f, 0.5f, 0.75f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Init camera
        Camera* camera = new Camera(glm::vec3(32, 10, 32), glm::radians(70.0f));


        float lastTime = glfwGetTime();
        float delta = 0.0f;
        const float speed = 6.0f;

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
            if (Events::jpressed(GLFW_KEY_F1)) {
                unsigned char* buffer = new unsigned char[chunks->m_volume * CHUNK_VOL];
                chunks->write(buffer);
                ResourceManager::saveWorld((const char*)buffer, chunks->m_volume * CHUNK_VOL, "1.txt");
                delete[] buffer;
            }
            if (Events::jpressed(GLFW_KEY_F2)) {
                unsigned char* buffer = new unsigned char[chunks->m_volume * CHUNK_VOL];
                ResourceManager::getWorld((char*)buffer, chunks->m_volume* CHUNK_VOL, "1.txt");
                chunks->read(buffer);
                delete[] buffer;
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
                camera->addY(speed * delta);
            }
            if (Events::pressed(GLFW_KEY_LEFT_CONTROL)) {
                camera->addY(-speed * delta);
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

            // raycast
            {
                glm::vec3 end;
                glm::vec3 norm;
                glm::vec3 iend;
                Voxel* vox = chunks->rayCast(camera->getPosition(), camera->getFront(), 10.0f, end, norm, iend);
                if (vox != nullptr) {
                    lineBatch->box(iend.x + 0.5f, iend.y + 0.5f, iend.z + 0.5f, 1.01f, 1.01f, 1.01f, 0,0,0,1);

                    if (Events::jclicked(GLFW_MOUSE_BUTTON_1)) {
                        chunks->set(int(iend.x), int(iend.y), int(iend.z), 0);
                    }
                    if (Events::jclicked(GLFW_MOUSE_BUTTON_2)) {
                        chunks->set(int(iend.x) + int(norm.x), int(iend.y) + int(norm.y), int(iend.z) + int(norm.z), 1);
                    }
                }
            }
            
            Chunk* closes[27 /* (3 * 3 * 3) */];
            for (int i = 0; i < chunks->m_volume; i++) {
                Chunk* chunk = chunks->m_chunks[i];
                if (!chunk->m_modified) {
                    continue;
                }
                chunk->m_modified = false;
                if (meshes[i] != nullptr) {
                    delete meshes[i];
                }

                for (int j = 0; j < 27; j++) {
                    closes[j] = nullptr;
                }
                for (uint32_t j = 0; j < chunks->m_volume; j++) {
                    Chunk* other = chunks->m_chunks[j];

                    int ox = other->m_x - chunk->m_x;
                    int oy = other->m_y - chunk->m_y;
                    int oz = other->m_z - chunk->m_z;

                    if (abs(ox) > 1 || abs(oy) > 1 || abs(oz) > 1) {
                        continue; //
                    }

                    ++ox;
                    ++oy;
                    ++oz;
                    closes[(oy * 3 + oz) * 3 + ox] = other;
                }

                meshes[i] = renderer.render(chunk, (const Chunk**)closes, true);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // DRAW VAO
            shader->use();
            shader->uniformMatrix("projview", (camera->getProjection())*(camera->getView()));
            texture->bind();
            glm::mat4 model(1.0f);
            for (uint32_t i = 0; i < chunks->m_volume; i++) {
                model = glm::translate(glm::mat4(1.0f), glm::vec3(chunks->m_chunks[i]->m_x * CHUNK_W + 0.5f, chunks->m_chunks[i]->m_y * CHUNK_H + 0.5f, chunks->m_chunks[i]->m_z * CHUNK_D + 0.5f)  );

                shader->uniformMatrix("model", model);
                meshes[i]->draw(GL_TRIANGLES);
            }
            cursorShader->use();
            cursorMesh->draw(GL_LINES);


            linesShader->use();
            linesShader->uniformMatrix("projview", (camera->getProjection()) * (camera->getView()));
            lineBatch->line(
                1.0f, 1.0f, 1.0f,
                1.0f, 10.0f, 1.0f,

                1.0f, 1.0f, 0.0f, 1.0f
            );
            glLineWidth(2.0f);
            lineBatch->render();


            /* Swap front and back buffers */
            MineTest::Window::swapBuffers();

            /* Poll for and process events */
            Events::poll();

        }

        delete cursorMesh;
        delete shader;
        delete cursorShader;
        delete texture;
        delete camera;
        delete chunks;
        delete lineBatch;


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