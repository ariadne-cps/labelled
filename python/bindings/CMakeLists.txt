include_directories(${Python3_INCLUDE_DIRS})

get_target_property(PYTHON_COMMON_SOURCE_DIR pyariadne-python-common SOURCE_DIR)

add_library(pyariadne-labelled-submodule-obj OBJECT
    labelled_submodule.cpp
)

target_include_directories(pyariadne-labelled-submodule-obj PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PYTHON_COMMON_SOURCE_DIR}/include"
    $<TARGET_PROPERTY:pyariadne-symbolic,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:pyariadne-function,INTERFACE_INCLUDE_DIRECTORIES>
)
target_link_libraries(pyariadne-labelled-submodule-obj PRIVATE
    pyariadne-python-common
    pybind11::module
    labelled
    pyariadne-symbolic
    pyariadne-function
)
set_target_properties(pyariadne-labelled-submodule-obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(pyariadne-labelled INTERFACE)
target_sources(pyariadne-labelled INTERFACE
    $<TARGET_OBJECTS:pyariadne-labelled-submodule-obj>
)
target_include_directories(pyariadne-labelled INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<TARGET_PROPERTY:pyariadne-symbolic,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:pyariadne-function,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(pyariadne-labelled INTERFACE
    pyariadne-symbolic pyariadne-function
)

ariadne_add_python_module(
    NAME labelled
    MODULE_IMPORT_NAME pyariadne_labelled
    MODULE_SOURCE labelled_module.cpp
)
