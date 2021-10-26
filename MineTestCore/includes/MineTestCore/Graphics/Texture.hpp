
#pragma once

#include <string>

namespace MineTest {
	
	class Texture {
	public:
		Texture(unsigned int id, int w, int h);
		~Texture();

		void bind();
	private:
		unsigned int m_id;
		int m_w;
		int m_h;
	};

	Texture* make_texture(const std::string& textureName);

}