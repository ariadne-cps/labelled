cmake_minimum_required(VERSION 3.15)
project(AriadneLabelledTutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(AriadneLabelled REQUIRED)

add_executable(tutorial_labelled tutorial_labelled.cpp)
target_link_libraries(tutorial_labelled PRIVATE AriadneLabelled::ariadne-labelled)
