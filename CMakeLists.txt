#cmake最小所需版本
cmake_minimum_required(VERSION 3.8)

project(ChatBot)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)