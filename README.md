# Isomet iMS Control Examples
A set of useful getting started guides for new users of the Isomet iMS Acousto-Optic Control Software system.

iMS is a technology developed by Isomet consisting of a range of RF hardware products designed for driving Acousto-Optic devices with complex patterns or sequences of fast modulating waveforms.  A suite of software applications and APIs are made available allowing customers to integrate the RF drivers into their own systems with substantial flexibility and control.

These examples demonstrate how to install the software in a development environment and introduce the new user to some key concepts when beginning the journey of developing an iMS based control system.

# Contents
* [Installing the library](#installing-the-library)
* [Setting up the Development Environment](#setting-up-the-development-environment)
* [Example 01: Getting Started](01-GettingStarted/README.md)
* [Example 02: Scanning for an iMS System](02-ScanConnect/README.md)

# Installing the library

## Operating System Support
These examples assume the user is familiar with software development in a Linux environment and show how to install the iMS shared library on an example 64-bit x86 platform running Ubuntu 20.04.

Windows users should download and install the SDK directly from the Isomet website: https://isomet.com/ims4_sw.html

For other platforms and Operating System requirements, please contact us at isomet@isomet.co.uk

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

If all goes well, the library and its supporting files should be installed to `/opt/isomet`

# Setting up the Development Environment

The examples in this repository use CMake and we recommend using Visual Studio Code to build them. Download and install the Visual Studio Code Debian/Ubuntu package from here: https://code.visualstudio.com/download

You will need the official Microsoft C++ extension: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools

And the CMake and CMake Tools extensions from here: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools

From a terminal, ensure that cmake and a few other build dependencies are installed:

`$ sudo apt install cmake build-essential gdb git`

You should now be ready to build the examples!

Continue to: [Example 01: Getting Started](01-GettingStarted/README.md)
