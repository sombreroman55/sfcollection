cmake_minimum_required(VERSION 3.10)

# set the project name
project(sfas-tester VERSION 0.0.1)

find_package(GTest CONFIG REQUIRED)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config.hh.in config.hh)

# add the executable
add_executable(sfas-tester main.cc)

target_include_directories(sfas-tester PUBLIC
                           "${PROJECT_BINARY_DIR}"
                          )
