cmake_minimum_required(VERSION 3.10)

project("ims-example-01" VERSION 1.0 DESCRIPTION "A project that just links to the iMS library")

# provide the library installation folder, so CMake could find its config
set(CMAKE_PREFIX_PATH "/opt/isomet")

# Look for the iMS Control library
find_package(ims 1.8.5 CONFIG REQUIRED)

# it is an application
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

# linking to the iMS library
target_link_libraries(${PROJECT_NAME} PRIVATE ims)
