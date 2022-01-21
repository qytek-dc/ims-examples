# Example 01: Getting Started

Create a working folder to compile these examples in and change directory to it:

`$ mkdir ims && cd ims`

Clone this git repository into your new directory:

`$ git clone https://github.com/qytek-dc/ims-examples.git`

Start VS Code and open the folder `~/ims/ims-examples`.  You will be prompted to choose a 'kit', in this case a compiler to build the examples with.  We will use GCC:

![Choose a kit](/images/choose-a-kit.png)

Along the status bar at the bottom, select the variant to build (default 'Debug')

![Variant](/images/getting-started-01.jpg)

Four options are present.  Stick with Debug for the moment:

![Variant Type](/images/cmake-variant-type.png)

Then click on Build:

![Build](/images/cmake-build.png)

If the build completes successfully, change the target in the status bar from [all] to [ims-example-01] and click Run to see the program output in the terminal window:

![Run](/images/getting-started-02.png)

If you see the message "This example is linked to iMS library Version: 1.8.5", you have successfully installed the iMS Control library and linked your first program to it!

![Run Result](/images/getting-started-03.png)

# Walkthrough

What happened here?

If you take a look into [main.cpp](#main.cpp) you'll see that there are only a handful of lines of code.

```cpp
#include "ims/LibVersion.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "This example is linked to iMS Library Version: " << iMS::LibVersion::GetVersion() << std::endl;

    return 0;
}
```

`iMS::LibVersion::GetVersion` is a static function that returns a std::string describing the version number of the library object.  Here we are using it simply to prove to ourselves that we have the library available and can link it into our application.

> **_NOTE:_** The **iMS** namespace is used for every class and function definition in the iMS library.  We have shown it here explicitly declared before `LibVersion` to highlight this fact.  You may wish to add the line `using namespace iMS;` into your applications to avoid having to write it before every function call and object instantiation.

So far, so straightforward, but how does the compiler know where to find `"ims/LibVersion.h"` and where does the linker look to find the library code?

## CMake "find_package"

Open up [CMakeLists.txt](CMakeLists.txt) and you'll find a couple of bits of 'magic' in there.  Let's walk it through:

```cmake
cmake_minimum_required(VERSION 3.10)
```
This is a required line by the CMake system.  You can set a minimum version of CMake that must be installed on the system for it to run successfully.  There is nothing in this project that needs a newer version of CMake than 3.10.

```cmake
project("ims-example-01" VERSION 1.0 DESCRIPTION "A project that just links to the iMS library")
```
This is also a required line which defines the project name, version number and a description

```cmake
# provide the library installation folder, so CMake could find its config
set(CMAKE_PREFIX_PATH "/opt/isomet")

# Look for the iMS Control library
find_package(ims 1.8.5 CONFIG REQUIRED)
```
`find_package` is a fantastic feature that allows CMake to search the development system for all the source files, build dependencies, compiler definitions and any other build information that is required by our application.  It will search the system folders first, but if we installed the library to the default location, we must tell it to look there by setting `CMAKE_PREFIX_PATH` to `/opt/isomet`.

We tell CMake that we REQUIRE the ims library to build our application.  If it can't find it, or it finds a version that is older than 1.8.5, it will fail to build.

If 'ims' is found by CMake's find_package, then all of the build information specified in the package's CMake files, along with include and library directories are added to this project's build without having to do any more work!

```cmake
# it is an application
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

# linking to the iMS library
target_link_libraries(${PROJECT_NAME} PRIVATE ims
```
Here we simply tell CMake that we are building an application, that it consists of one source file and that we would like to link to the `ims` library that we previously found.

Simple? Great! Let's move on to some more interesting examples... [Scanning for an iMS System](/02-ScanConnect/README.md)