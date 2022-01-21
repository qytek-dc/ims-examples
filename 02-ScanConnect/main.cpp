#include "IMSConnection.h"
#include <ims/LibVersion.h>
#include <iostream>

// A single reference to the connection between our application and the hardware
IMSConnection conn;

// This becomes a pointer to the ims hardware which we can use to interact with it
iMS::IMSSystem * myiMS = nullptr ;

static void RunExample(void)
{
    int ims_count = 0, i = 0;

    conn.Scan();

    // Display results to user and ask user to choose a system  
    std::cout << "Discovered " << conn.List().size() << " iMS Systems: " << std::endl;
    for (std::vector<iMS::IMSSystem>::const_iterator it = conn.List().cbegin();
        it != conn.List().cend(); ++it) {
        std::cout << "  " << ++ims_count << ") " << it->ConnPort() << std::endl;
    }

    if (ims_count) {
        // Request user input
        while ((i < 1) || (i > ims_count) || std::cin.fail()) {
            std::cout << "Select a system to connect (1-" << ims_count << ")? ";
            std::cin >> i;
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }

        // Obtain our hardware pointer
        myiMS = &conn.List().at(i-1);
    } else {
        std::cout << "<none found> ..." << std::endl;
        return;
    }

    std::cout << "Connecting to " << myiMS->ConnPort() << std::endl;
    myiMS->Connect();

    const iMS::IMSSynthesiser& syn = myiMS->Synth();
    const iMS::IMSController& ctlr = myiMS->Ctlr();

    std::cout << std::endl;

    if (syn.IsValid()) {
        std::cout << "Found Synthesiser: " << syn.Model() << " : " << syn.Description() << std::endl;
        std::cout << "  FW version: " << syn.GetVersion() << std::endl;
        std::cout << "  LF: " << syn.GetCap().lowerFrequency << "MHz  UF: " << syn.GetCap().upperFrequency << "MHz" << std::endl;
    }

    std::cout << std::endl;

    if (ctlr.IsValid()) {
        std::cout << "Found Controller: " << ctlr.Model() << " : " << ctlr.Description() << std::endl;
        std::cout << "  FW version: " << ctlr.GetVersion() << std::endl;
        std::cout << "  Max Image Points: " << ctlr.GetCap().MaxImageSize << std::endl;
        std::cout << "  Max Image Rate: " << ctlr.GetCap().MaxImageRate << std::endl;
    }

    // That's all for this example. 
    std::cout << std::endl;
    std::cout << "Disconnecting.." << std::endl;
    myiMS->Disconnect();
}

int main(int argc, char** argv)
{
    std::cout << "iMS Example 02: Connecting to an iMS System" << std::endl;
    std::cout << "Using iMS Library Version: " << iMS::LibVersion::GetVersion() << std::endl;
    std::cout << "Scanning for iMS Systems... please wait..." << std::endl;

    RunExample();

    return 0;
}