
#pragma once

#include <MineTestCore/Window.hpp>

namespace MineTest {

	using uint = unsigned int;

	

	class Events {
	public:
		static int initialization();
		static int finalization();
		static void poll();
	public:
		static bool pressed(int keycode);
		static bool jpressed(int keycode);
		static bool clicked(int buttom);
		static bool jclicked(int buttom);

	public:
		static bool* m_keys;
		static uint* m_frames;
		static uint m_current;
		static float m_deltaX;
		static float m_deltaY;
		static float m_x;
		static float m_y;
		static bool m_cursor_locked;

	public:
		static const int _MOUSE_BUTTONS_POS = 1024;
	};

}