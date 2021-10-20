
#pragma once

namespace MineTest {

	class Application {
	public:
		int initialization(int w, int h, const char* title);
		int start();
		int finalization();
		virtual void doing() {}
	};

}