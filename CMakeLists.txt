cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 17)
project(monitor)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(monitor ${SOURCES})

add_executable(test test/test.cpp src/linux_parser.cpp src/format.cpp src/process.cpp src/processor.cpp src/system.cpp)

set_property(TARGET monitor PROPERTY CXX_STANDARD 17)
target_link_libraries(monitor ${CURSES_LIBRARIES})
# TODO: Run -Werror in CI.
target_compile_options(monitor PRIVATE -Wall -Wextra)
