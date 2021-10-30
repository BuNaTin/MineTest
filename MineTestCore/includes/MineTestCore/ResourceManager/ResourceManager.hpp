
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
        static bool saveWorld(const char buffer[], size_t size, const std::string& world_name);
        static void getWorld(char* buffer, size_t size, const std::string& world_name);
    private:
        static std::string m_currentFolder;
    };
}