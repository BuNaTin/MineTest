
#include "../includes/MineTestCore/Graphics/Texture.hpp"

#include <MineTestCore/ResourceManager/ResourceManager.hpp>

#include <MineTestCore/Graphics/myglad.hpp>

namespace MineTest {

	Texture::Texture(unsigned int id, int w, int h) : m_id(id),m_w(w), m_h(h) {

	}
	Texture::~Texture() {
		glDeleteTextures(1, &m_id);
	}
	void Texture::bind() {
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	Texture* make_texture(const std::string& textureName) {

		PNG pic = ResourceManager::read_PNG(textureName);
		if (pic._data == nullptr) {
			CONSOLE_LOG_ERROR("[Texture] Wrong texture");
		}
		GLuint texture;
		glGenTextures(1, &texture); 
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pic._w, pic._h, 0, 
			GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pic._data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (texture == 0) {
			CONSOLE_LOG_ERROR("[Texture] Wrong texture {0}", textureName);
			return nullptr;
		}
		return new Texture(texture, pic._w, pic._h);
	}
}