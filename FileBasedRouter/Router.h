#pragma once

#include <string>
#include <map>
#include <vector>
#include <filesystem>

struct RouterRequest
{
    std::string method;
    std::string path;
};

struct RouterResponse
{
    int status;
    std::string body;
};
namespace fs = std::filesystem;

struct LineColor
{
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
};

class Router
{
    private:
        LineColor lineColor;
        std::map<std::string, std::string> routes;
        bool checkDir(const std::string& configFilePath);
        bool add(const std::string& path, const std::string& filePath);
        void handleError(const fs::filesystem_error& error);


    public:
        void help();
        void autoSetUp(Router router, const std::string& pathRouters);
        void initialize();
        bool load(const std::string& configFilePath);
        void create(const std::string& path, const std::string& filePath);
        void remove(const std::string& path, const std::string& filePath);
};

