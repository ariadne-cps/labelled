add_library(LABELLING_SRC OBJECT
    point.cpp
    curve.cpp
    figure.cpp
)

target_include_directories(LABELLING_SRC PRIVATE
    "${PROJECT_SOURCE_DIR}/include/labelling"
)
