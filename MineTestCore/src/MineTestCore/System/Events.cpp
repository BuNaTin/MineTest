
#include "../includes/MineTestCore/System/Events.hpp"

#include <MineTestCore/System/Log.hpp>
#include <MineTestCore/System/Window.hpp>

// for memset()
#include <cstring>

#include <iostream>

#include <MineTestCore/Graphics/myglad.hpp>
#include <GLFW/glfw3.h>



namespace MineTest {

	bool* Events::m_keys;
	uint* Events::m_frames;
	uint Events::m_current = 0;
	float Events::m_deltaX = 0.0f;
	float Events::m_deltaY = 0.0f;
	float Events::m_x = 0.0f;
	float Events::m_y = 0.0f;
	bool Events::m_cursor_locked = false;
	bool Events::m_cursor_started = false;

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		if (!Events::m_cursor_started) {
			Events::m_deltaX += static_cast<float>(xpos - Events::m_x);
			Events::m_deltaY += static_cast<float>(ypos - Events::m_y);
		}
		else {
			Events::m_cursor_started = true;
		}
		Events::m_x = static_cast<float>(xpos);
		Events::m_y = static_cast<float>(ypos);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
		if (action == GLFW_PRESS) {
			Events::m_keys[Events::_MOUSE_BUTTONS_POS + button] = true;
			Events::m_frames[Events::_MOUSE_BUTTONS_POS + button] = Events::m_current;
		}
		else if (action == GLFW_RELEASE) {
			Events::m_keys[Events::_MOUSE_BUTTONS_POS + button] = false;
			Events::m_frames[Events::_MOUSE_BUTTONS_POS + button] = Events::m_current;
		}
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		if (action == GLFW_PRESS) {
			Events::m_keys[key] = true;
			Events::m_frames[key] = Events::m_current;
		}
		else if (action == GLFW_RELEASE) {
			Events::m_keys[key] = false;
			Events::m_frames[key] = Events::m_current;
		}
	}

	void window_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		Window::setW(width);
		Window::setH(height);
	}

	int Events::initialization() {

		// GLFWwindow* window = Window::window;
		GLFW_KEY_ESCAPE;
		m_keys = new bool[1032];
		m_frames = new uint[1032];

		memset(m_keys, false, 1032 * sizeof(bool));
		memset(m_frames, 0, 1032 * sizeof(uint));

		// set callbacks
		glfwSetKeyCallback(Window::get(), key_callback);
		glfwSetMouseButtonCallback(Window::get(), mouse_button_callback);
		glfwSetCursorPosCallback(Window::get(), cursor_position_callback);
		glfwSetWindowSizeCallback(Window::get(), window_size_callback);
		// end setting callbacks

		CONSOLE_LOG_INFO("[Events] Initialization done");
		return 0;
	}
	int Events::finalization() {
		CONSOLE_LOG_INFO("[Events] Finalization done");
		//
		return 0;
	}

	void Events::poll() {
		m_current++;
		m_deltaX = 0.0f;
		m_deltaY = 0.0f;


		glfwPollEvents();
	}

	void Events::toogleCursor() {
		m_cursor_locked = !m_cursor_locked;
		Window::setCursorMode(m_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}

	bool Events::pressed(int keycode) {
		if (keycode < 0 || keycode >= _MOUSE_BUTTONS_POS) {
			return false;
		}
		return m_keys[keycode];
	}

	bool Events::jpressed(int keycode) {
		if (keycode < 0 || keycode >= _MOUSE_BUTTONS_POS) {
			return false;
		}
		return m_keys[keycode] && m_frames[keycode] == m_current;
	}

	bool Events::clicked(int buttom) {
		int index = _MOUSE_BUTTONS_POS + buttom;
		return m_keys[index];
	}

	bool Events::jclicked(int buttom) {
		int index = _MOUSE_BUTTONS_POS + buttom;
		return m_keys[index] && m_frames[index] == m_current;
	}
}