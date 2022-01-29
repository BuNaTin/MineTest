
#include "../includes/MineTestCore/Input/InputHandler.hpp"
#include "../includes/MineTestCore/System/Events.hpp"
#include "../includes/MineTestCore/Input/Commands.hpp"
#include "GLFW/glfw3.h"

namespace MineTest {

	int InputHandler::poll() noexcept {
		Events::poll(); 

        // shouldn't stay in aplication.cpp
        if (Events::jpressed(GLFW_KEY_TAB)) {
            Events::toogleCursor();
        }

        if (Events::m_cursor_locked) {
            CameraCommands.push(new CameraRotate());
        }
        if (Events::pressed(GLFW_KEY_W)) {
            CameraCommands.push(new CameraMoveForward());
        }
        if (Events::pressed(GLFW_KEY_S)) {
            CameraCommands.push(new CameraMoveBack());
        }
        if (Events::pressed(GLFW_KEY_D)) {
            CameraCommands.push(new CameraMoveRight());
        }
        if (Events::pressed(GLFW_KEY_A)) {
            CameraCommands.push(new CameraMoveLeft());
        }
        if (Events::pressed(GLFW_KEY_SPACE)) {
            CameraCommands.push(new CameraMoveUp());
        }
        if (Events::pressed(GLFW_KEY_LEFT_CONTROL)) {
            CameraCommands.push(new CameraMoveDown());
        }
        return 0;
	}

    std::vector<CameraCommand*> InputHandler::getCameraCommand() noexcept {
        if (CameraCommands.empty()) {
            return std::vector< CameraCommand* > {new CameraAfk()};
        }
        else {
            std::vector< CameraCommand*> answer;
            while (!CameraCommands.empty()) {
                answer.push_back(CameraCommands.front());
                CameraCommands.pop();
            }
            return answer;
        }
    }

    bool InputHandler::getBreakCommand() const noexcept {
        return (Events::jclicked(GLFW_MOUSE_BUTTON_1));
    }
    bool InputHandler::getPutCommand() const noexcept {
        return (Events::jclicked(GLFW_MOUSE_BUTTON_2));
    }
}