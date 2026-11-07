add_library(LABELLED_SRC OBJECT
    point.cpp
    curve.cpp
    figure.cpp
    labelled_augmented_paving.cpp
)

target_include_directories(LABELLED_SRC PRIVATE
    "${PROJECT_SOURCE_DIR}/include/labelled"
)
