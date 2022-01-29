
#pragma once

#include <queue>
#include <vector>
#include "Commands.hpp"


namespace MineTest {

	class InputHandler {
	private:
		std::queue<CameraCommand*> CameraCommands;
	public:
		int poll() noexcept;
		std::vector<CameraCommand*> getCameraCommand() noexcept;
		bool getBreakCommand() const noexcept;
		bool getPutCommand() const noexcept;
	};

}