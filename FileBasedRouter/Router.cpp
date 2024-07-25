#include "Router.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>

void Router::help()
{
    std::cout << lineColor.WHITE
        << "[-] help menu"
        << std::endl
        << lineColor.RESET;
}

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
        handleError(error);
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
        handleError(error);
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


void Router::create(const std::string& path, const std::string& filePath)
{
    std::ofstream outfile(filePath);
    if (outfile.is_open())
    {
        routes[path] = filePath;
        outfile.close();
        std::cout << lineColor.GREEN
            << "[-] File created: " << filePath << "\n"
            << lineColor.RESET;
    }
    else
    {
        std::cerr << lineColor.RED
            << "[!] Failed to create file: " << filePath << "\n"
            << lineColor.RESET;
    }
}

void Router::remove(const std::string& path, const std::string& filePath)
{
    namespace fs = std::filesystem;
    try
    {
        if (fs::remove(filePath))
        {
            routes.erase(path);
            std::cout << lineColor.GREEN
                << "[-] File deleted: " << filePath << "\n"
                << lineColor.RESET;
        }
        else
        {
            std::cerr << lineColor.RED
                << "[!] Failed to delete file: " << filePath << "\n"
                << lineColor.RESET;
        }
    }
    catch (const fs::filesystem_error& error)
    {
        handleError(error);
    }
}

void Router::handleError(const fs::filesystem_error& fsError)
{
    std::cerr << lineColor.RED
        << "[!] Filesystem error: "
        << fsError.what()
        << lineColor.RESET
        << std::endl;
}