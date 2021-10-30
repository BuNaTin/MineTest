
#pragma once

#include <MineTestCore/System/Log.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MineTest {
	class glad {
	public:

		static void init() {
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				CONSOLE_LOG_CRITICAL("[glad] Fail init");
			}
		}

		static void glClear() {
			::glClear(GL_COLOR_BUFFER_BIT);
		}

		static void glClearColor(float x, float y, float z, float w) {
			::glClearColor(x, y, z, w);
		}
	
	};
}