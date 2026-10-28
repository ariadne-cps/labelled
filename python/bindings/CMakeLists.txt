include_directories(${Python3_INCLUDE_DIRS})

get_target_property(PYTHON_COMMON_SOURCE_DIR pyariadne-python-common SOURCE_DIR)

add_library(pyariadne-labelling-submodule-obj OBJECT
    labelling_submodule.cpp
)

target_include_directories(pyariadne-labelling-submodule-obj PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PYTHON_COMMON_SOURCE_DIR}/include"
    $<TARGET_PROPERTY:pyariadne-expression_set,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:pyariadne-drawing,INTERFACE_INCLUDE_DIRECTORIES>
)
target_link_libraries(pyariadne-labelling-submodule-obj PRIVATE
    pyariadne-python-common
    pybind11::module
    labelling
)
set_target_properties(pyariadne-labelling-submodule-obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(pyariadne-labelling INTERFACE)
target_sources(pyariadne-labelling INTERFACE
    $<TARGET_OBJECTS:pyariadne-labelling-submodule-obj>
)
target_include_directories(pyariadne-labelling INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<TARGET_PROPERTY:pyariadne-expression_set,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:pyariadne-drawing,INTERFACE_INCLUDE_DIRECTORIES>
)
target_link_libraries(pyariadne-labelling INTERFACE
    pyariadne-expression_set
    pyariadne-drawing
)

ariadne_add_python_module(
    NAME labelling
    MODULE_SOURCE labelling_module.cpp
)
