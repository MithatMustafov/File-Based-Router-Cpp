#include "router.h"
#include <string>

int main()
{
    Router router;
    std::string pathRoutersFolder = "Router_Pages";
    router.autoSetUp(router, pathRoutersFolder);

    return 0;
}
