project(NeuralNetwork)
cmake_minimum_required(VERSION 2.8)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(src)


add_definitions(-std=c++11)
  
file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE header_files src/*.h)

add_executable(${PROJECT_NAME} ${source_files} ${header_files})

