
#include "../includes/MineTestCore/Graphics/Camera.hpp"

#include <MineTestCore/Window.hpp>
#include <glm/ext.hpp>

namespace MineTest {

	Camera::Camera(glm::vec3 position, float fov) : m_position(position), m_fov(fov), m_rotation(1.0f) {
		updateVectors();
	}

	void Camera::updateVectors() {
		m_front = static_cast<glm::vec3>( m_rotation * glm::vec4(0, 0, -1, 1) );
		m_right = static_cast<glm::vec3>( m_rotation * glm::vec4(1, 0, 0, 1) );
		m_up = static_cast<glm::vec3>( m_rotation * glm::vec4(0, 1, 0, 1) );
	}

	void Camera::resetRotation() {
		m_rotation = glm::mat4(1.0f);
	}

	void Camera::addPosition(glm::vec3 alpha) {
		m_position += alpha;
	}

	void Camera::addY(float a) {
		m_position.y += a;
	}

	glm::vec3 Camera::getPosition() const {
		return m_position;
	}
	glm::vec3 Camera::getFront() const {
		return m_front;
	}
	glm::vec3 Camera::getRight() const {
		return m_right;
	}
	void Camera::rotate(float x, float y, float z) {
		m_rotation = glm::rotate(m_rotation, z, glm::vec3(0, 0, 1));
		m_rotation = glm::rotate(m_rotation, y, glm::vec3(0, 1, 0));
		m_rotation = glm::rotate(m_rotation, x, glm::vec3(1, 0, 0));

		updateVectors();
	}

	glm::mat4 Camera::getProjection() const {
		float aspect = static_cast<float>(Window::getW()) / static_cast<float>(Window::getH());
		return glm::perspective(m_fov, aspect, 0.1f, 100.0f);
	}

	glm::mat4 Camera::getView() const {
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}
}