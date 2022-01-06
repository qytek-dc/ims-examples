# Isomet iMS Control Examples
Set of useful getting started guides for use with the Isomet iMS Acousto-Optic Control Software Library

# Installing the library

## Windows 10 / 11

Please download and install the SDK directly from the Isomet website: https://isomet.com/ims4_sw.html

## Ubuntu 20.04 LTS (64-bit)

The library can be installed directly from an APT repository.  Open a terminal and follow these instructions:

* Request Isomet's public code signing key from the Ubuntu Key Exchange server

`$ sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 41C50D84`
* Install the apt-add-repository helper script

`$ sudo apt install software-properties-common`
* Tell Apt where to find the iMS repository

`$ sudo apt-add-repository "deb http://isomet-ims-lib.s3.amazonaws.com focal main"`
* Update Apt

`$ sudo apt update`
* Install the library together with its dependency on libxml2

`$ sudo apt install libxml2-dev libims`

If all goes, the library and its supporting files should be installed to `/opt/isomet`

# Setting up the Development Environment

The examples in this repository use CMake and we recommend using Visual Studio Code to build them.  Follow these instructions to get started for your platform (https://code.visualstudio.com/docs/cpp).  Ensure the C++ extension by Microsoft is installed.

On Ubuntu, ensure cmake is installed:

`$ cmake --version`

and install the GCC compiler:

`$ sudo apt install build-essential gdb git`

You should now be ready to build the examples!

# Building the Examples

If you haven't already, download this git repository:

`$ git clone https://github.com/qytek-dc/ims-examples.git`

Open VS Code and open the folder where the repository was downloaded.

Along the status bar at the bottom, select the variant to build (default 'Debug')

![Variant](/images/getting-started-01.jpg)

![Variant Type](/images/cmake-variant-type.png)

Then click on Build:

![Build](/images/cmake-build.png)

If the build completes successfully, select the target (ims-example-01) and click Run to see the program output in the terminal window:

![Run](/images/getting-started-02.png)

If you see the message "This example is linked to iMS library Version: 1.8.5", you have successfully installed the iMS Control library and linked your first program to it!

![Run Result](/images/getting-started-03.png)

