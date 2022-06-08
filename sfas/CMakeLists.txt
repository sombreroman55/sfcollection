cmake_minimum_required(VERSION 3.10)

# set the project name
project(sfas VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config.hh.in config.hh)

# add the executable
add_executable(sfas)

target_sources(sfas PUBLIC
               "${PROJECT_SOURCE_DIR}/main.cc"
               "${PROJECT_SOURCE_DIR}/src/lexer.cc"
               "${PROJECT_SOURCE_DIR}/src/location.cc"
               "${PROJECT_SOURCE_DIR}/src/token.cc"
              )

target_include_directories(sfas PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src"
                          )
