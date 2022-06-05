cmake_minimum_required(VERSION 3.10)

# set the project name
project(sfas VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config.hh.in config.hh)

# add the executable
add_executable(sfas main.cc)

target_include_directories(sfas PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src"
                          )
