
#include "../includes/MineTestCore/ResourceManager.hpp"

#include <MineTestCore/Log.hpp>

#include <string>
#include <fstream>
#include <sstream>

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

		std::string fileName = m_currentFolder + "\\res\\" + shader_name;

		ShaderFile.open(fileName);

		if (!ShaderFile.is_open()) {
			CONSOLE_LOG_CRITICAL("[Shader] Can't load shader");
			return "";
		}
		ShaderStream << ShaderFile.rdbuf();

		ShaderFile.close();

		Code = ShaderStream.str();

		return Code;
	}
}