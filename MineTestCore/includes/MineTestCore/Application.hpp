
#pragma once

namespace MineTest {

	class Application {
	public:
		int initialization(int w, int h, const char* title, const char* exe_folder);
		int start();
		int finalization();
		virtual void doing() {}
	};

}