
#include "../includes/MineTestCore/Input/Commands.hpp"
#include "../includes/MineTestCore/Graphics/Camera.hpp"
#include "../includes/MineTestCore/System/Events.hpp"
#include "../includes/MineTestCore/System/Window.hpp"

namespace MineTest {
	
	int CameraMoveForward::execute(Camera* camera, float delta, float speed) {
		camera->addPosition(camera->getFront() * delta * speed);
		return 0;
	}
	int CameraMoveBack::execute(Camera* camera, float delta, float speed) {
		camera->addPosition(-camera->getFront() * delta * speed);
		return 0;
	}
	int CameraMoveRight::execute(Camera* camera, float delta, float speed) {
		camera->addPosition(camera->getRight() * delta * speed);
		return 0;
	}
	int CameraMoveLeft::execute(Camera* camera, float delta, float speed) {
		camera->addPosition(-camera->getRight() * delta * speed);
		return 0;
	}
	int CameraMoveUp::execute(Camera* camera, float delta, float speed) {
		camera->addY(speed * delta);
		return 0;
	}
	int CameraMoveDown::execute(Camera* camera, float delta, float speed) {
		camera->addY(-speed * delta);
		return 0;
	}
	int CameraRotate::execute(Camera* camera, float delta, float speed) {
		camera->oldY -= (Events::m_deltaY / Window::getH());
		camera->oldX -= (Events::m_deltaX / Window::getW());
		if (camera->oldY < -glm::radians(89.0f)) {
			camera->oldY = -glm::radians(89.0f);
		}
		if (camera->oldY > glm::radians(89.0f)) {
			camera->oldY = glm::radians(89.0f);
		}

		camera->resetRotation();
		camera->rotate(camera->oldY, camera->oldX, 0);
		return 0;
	}
	int CameraAfk::execute(Camera* camera, float delta, float speed) {
		// doing raycast staying afk!!!

		return 0;
	}

}