
#pragma once

#include <glm/glm.hpp>

namespace MineTest {

	class Camera {
	public:
		Camera(glm::vec3 position, float fov);

		glm::mat4 getProjection() const;
		glm::mat4 getView() const;

		void resetRotation();

		void addPosition(glm::vec3);
		void addY(float a);

		glm::vec3 getRight() const;
		glm::vec3 getFront() const;
		glm::vec3 getPosition() const;

		float oldX = 0.0f;
		float oldY = 0.0f;

		void rotate(float x, float y, float z);
	private:
		void updateVectors();

	private:
		glm::mat4 m_rotation;

		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;

		glm::vec3 m_position;
		float m_fov;
	};

}