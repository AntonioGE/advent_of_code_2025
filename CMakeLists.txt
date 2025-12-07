cmake_minimum_required(VERSION 3.10)

project(advent_2025)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

foreach(i RANGE 1 3)
    add_executable(advent_${i} src/advent_${i}.cpp src/advent_${i}.hpp)
endforeach()

# Copy the "res" folder into the binary folder
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
