cmake_minimum_required(VERSION 3.15)

project(Labelled VERSION 1.0)

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)

if(NOT TARGET ariadne-configuration)
    find_package(Git REQUIRED)
    execute_process(COMMAND "${GIT_EXECUTABLE}" -C "${CMAKE_CURRENT_SOURCE_DIR}"
                    submodule update --init -- ss/cfg
                    RESULT_VARIABLE _result)
    if(_result)
        message(FATAL_ERROR "Cannot initialize configuration submodule")
    endif()
    include("${CMAKE_CURRENT_SOURCE_DIR}/ss/cfg/cmake/ProjectOptions.cmake")
endif()

if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
    require_same_dependency_commit(Configuration
        CHAINS
            "configuration"
            "expression-set|configuration"
            "expression-set|symbolic|configuration"
            "expression-set|set|configuration"
            "drawing|configuration"
            "drawing|paving|configuration"
    )
    require_same_dependency_commit(Set
        CHAINS
            "expression-set|set"
            "drawing|paving|set"
    )
    require_same_dependency_commit(Function
        CHAINS
            "expression-set|symbolic|function"
            "expression-set|set|constraint-solving|nonlinear-programming|function"
    )
endif()

setup_project()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(ss)

add_library(labelled INTERFACE)
target_include_directories(labelled INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/ariadne-labelled>
)
target_link_libraries(labelled INTERFACE expression_set drawing)

add_subdirectory(src)
target_link_libraries(LABELLED_SRC PRIVATE labelled)

ariadne_register_public_headers(
    TARGET labelled
    DIRECTORIES "${PROJECT_SOURCE_DIR}/include/labelled"
    FILES "${PROJECT_SOURCE_DIR}/include/ariadne-labelled.hpp"
)

setup_project_library(
    TARGET ariadne-labelled
    OBJECTS LABELLED_SRC
    LINK_LIBRARIES labelled
)

setup_standalone_project_tests(
    TARGET ariadne-labelled
    TEST_DIRECTORY tests
    TEST_TARGET tests
    SOURCES
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/src"
)

if(BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif()

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    ariadne_install_dependency_bundle(
        TARGET labelled
        DESTINATION include/ariadne-labelled
    )
endif()
