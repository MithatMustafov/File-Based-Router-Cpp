#include "Router.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>

void Router::autoSetUp(Router router, const std::string& pathRouters)
{
    router.initialize();
    router.load(pathRouters);
}

void Router::initialize()
{
    routes.clear();
    std::cout << lineColor.GREEN
        << "[-] Router initialized."
        << lineColor.RESET
        << std::endl;
}

bool Router::load(const std::string& pathRouters)
{
    if (!checkDir(pathRouters)) return false;

    namespace fs = std::filesystem;
    try
    {
        std::string path, filePath;
        std::cout << lineColor.YELLOW
            << "[-] Route added: "
            << lineColor.RESET
            << std::endl;
        for (const auto& entry : fs::directory_iterator(pathRouters))
        {
            if (entry.is_regular_file())
            {
                path = "\\" + entry.path().stem().string();
                filePath = entry.path().string();
                add(path, filePath);
            }
        }
    }
    catch (const fs::filesystem_error& error)
    {
        std::cerr << lineColor.RED
            << "[!] Filesystem error: "
            << error.what()
            << lineColor.RESET
            << std::endl;
        return false;
    }
}

bool Router::checkDir(const std::string& pathRouters)
{
    namespace fs = std::filesystem;

    try
    {
        if (fs::exists(pathRouters) && fs::is_directory(pathRouters))
        {
            std::cout << lineColor.GREEN
                << "[-] The folder exists."
                << lineColor.RESET
                << std::endl;
            return true;
        }
    }
    catch (const fs::filesystem_error& error)
    {
        std::cerr << lineColor.RED
            << "[!] Filesystem error: "
            << error.what()
            << lineColor.RESET
            << std::endl;
        return false;
    }
}

bool Router::add(const std::string& path, const std::string& filePath)
{
    routes[path] = filePath;
    std::cout << lineColor.YELLOW  
        << "[-] " << path << " -> " << filePath << "\n"
        << lineColor.RESET;
    return true;
}