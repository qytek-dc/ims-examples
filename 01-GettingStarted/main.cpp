#include <ims/LibVersion.h>
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "This example is linked to iMS Library Version: " << iMS::LibVersion::GetVersion() << std::endl;

    return 0;
}