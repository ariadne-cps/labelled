cmake_minimum_required(VERSION 3.15)
project(AriadneLabellingTutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(AriadneLabelling REQUIRED)

add_executable(tutorial_labelling tutorial_labelling.cpp)
target_link_libraries(tutorial_labelling PRIVATE AriadneLabelling::ariadne-labelling)
