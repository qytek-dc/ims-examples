#include "IMSConnection.h"
#include <ims/LibVersion.h>
#include <iostream>

// A single reference to the connection between our application and the hardware
IMSConnection conn;

// This becomes a single reference to the ims hardware itself
static std::shared_ptr < iMS::IMSSystem > myiMS;

static void RunExample(void)
{
    int ims_count = 0, i;

    conn.Scan();

    // Display results to user and ask user to choose a system  
    std::cout << "Discovered " << conn.List().size() << " iMS Systems: " << std::endl;
    for (std::vector<iMS::IMSSystem>::const_iterator it = conn.List().cbegin();
        it != conn.List().cend(); ++it) {
            std::cout << "  " << ims_count++ << ") " << it->ConnPort() << std::endl;
        }
    if (ims_count) {
        while (i < 0 && i >= ims_count) {
            std::cout << "Select a system to connect to:";
            std::cin >> i;
            *myiMS = conn.List().at(i);
        }
    } else {
        std::cout << "<none found> ..." << std::endl;
        return;
    }
}

int main(int argc, char** argv)
{
    std::cout << "iMS Example 02: Connecting to an iMS System" << std::endl;
    std::cout << "Using iMS Library Version: " << iMS::LibVersion::GetVersion() << std::endl;
    std::cout << "Scanning for iMS Systems... please wait..." << std::endl;

    RunExample();

    return 0;
}