
#pragma once

#include <string>

#include <MineTestCore/Graphics/PNG.hpp>

namespace MineTest {
    class ResourceManager {
    public:
        static int initialization(const std::string& exe_folder);
        static int finalization();
    public:
        static std::string read_shader(const std::string& shader_name);
        static PNG read_PNG(const std::string& PNG_name);

    private:
        static std::string m_currentFolder;
    };
}