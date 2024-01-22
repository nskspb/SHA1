cmake_minimum_required(VERSION 3.5)

project(SHA-1)


add_executable(SHA-1
main.cpp)
set_target_properties(SHA-1 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)