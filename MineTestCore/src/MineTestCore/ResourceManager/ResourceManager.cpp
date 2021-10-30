
#include "../includes/MineTestCore/ResourceManager/ResourceManager.hpp"

#include <MineTestCore/System/Log.hpp>


#include <MineTestCore/Graphics/PNG.hpp>

#include <string>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <MineTestCore/ResourceManager/stb_image.hpp>


namespace MineTest{

	std::string ResourceManager::m_currentFolder = "";

	int ResourceManager::initialization(const std::string& exe_folder) {
		m_currentFolder = exe_folder;
		std::size_t a = m_currentFolder.find_last_of('\\');
		m_currentFolder = m_currentFolder.substr(0, a);
		a = m_currentFolder.find_last_of('\\');
		m_currentFolder = m_currentFolder.substr(0, a);
		a = m_currentFolder.find_last_of('\\');
		m_currentFolder = m_currentFolder.substr(0, a);
		a = m_currentFolder.find_last_of('\\');
		m_currentFolder = m_currentFolder.substr(0, a);
		m_currentFolder += "\\MineTestCore";

		CONSOLE_LOG_INFO("[ResourceManager] Initialization done");

		return 0;
	}
	int ResourceManager::finalization() {

		CONSOLE_LOG_INFO("[ResourceManager] Finalization done");

		return 0;
	}

	std::string ResourceManager::read_shader(const std::string& shader_name) {
		std::string Code;
		std::ifstream ShaderFile;
		std::stringstream ShaderStream;

		std::string fileName = m_currentFolder + "\\res\\shader\\" + shader_name;

		ShaderFile.open(fileName);

		if (!ShaderFile.is_open()) {
			CONSOLE_LOG_CRITICAL("[Shader] Can't load shader {0}", shader_name);
			return "";
		}
		ShaderStream << ShaderFile.rdbuf();

		ShaderFile.close();

		Code = ShaderStream.str();

		return Code;
	}

	PNG ResourceManager::read_PNG(const std::string& PNGname) {
		std::string PNGfileName = m_currentFolder + "\\res\\img\\" + PNGname;
		PNG pic;
		pic._type = PNGtype::RGBA;
		int comp;
		pic._data = stbi_load(PNGfileName.c_str(), &pic._w, &pic._h, &comp, static_cast<int>(pic._type));
		if (pic._data == nullptr) {
			CONSOLE_LOG_ERROR("[ResourceManager] Can't load PNG {0}", PNGname);
		}
		if (comp != 4) {
			CONSOLE_LOG_WARN("[ResourceManager] Texture {0} is not RGBA ( level = {1} )", PNGname, comp);
			pic._type = PNGtype::RGB;
		}
		return pic;
	}
	
	bool ResourceManager::saveWorld(const char buffer[], size_t size, const std::string& world_name)
	{
		std::string fileName = m_currentFolder + "\\res\\worlds\\" + world_name;
		std::ofstream worldFile(fileName);
		if (!worldFile.is_open()) {
			CONSOLE_LOG_CRITICAL("[World save] Can't open file {0}", world_name);
			return false;
		}
		std::ostringstream output;
		for (size_t i = 0; i < size; i++) {
			output << buffer[i];
		}
		worldFile << output.str();

		return true;
	}

	void MineTest::ResourceManager::getWorld(char* buffer, size_t size, const std::string& world_name)
	{
		std::string fileName = m_currentFolder + "\\res\\worlds\\" + world_name;
		std::ifstream worldFile(fileName);
		if (!worldFile.is_open()) {
			CONSOLE_LOG_CRITICAL("[World save] Can't open file {0}", world_name);
			return;
		}
		worldFile.read(buffer, size);

	}

}