find_library(ARIADNE_LABELLING_LIBRARY NAMES ariadne-labelling)
find_path(ARIADNE_LABELLING_INCLUDE_DIR ariadne-labelling.hpp
          PATH_SUFFIXES ariadne-labelling)

find_package(Threads REQUIRED)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AriadneLabelling DEFAULT_MSG
    ARIADNE_LABELLING_LIBRARY
    ARIADNE_LABELLING_INCLUDE_DIR
)

if(AriadneLabelling_FOUND)
    get_filename_component(ARIADNE_LABELLING_INCLUDE_PARENT_DIR
        "${ARIADNE_LABELLING_INCLUDE_DIR}" DIRECTORY)
    if(NOT TARGET AriadneLabelling::ariadne-labelling)
        add_library(AriadneLabelling::ariadne-labelling UNKNOWN IMPORTED)
        set_target_properties(AriadneLabelling::ariadne-labelling PROPERTIES
            IMPORTED_LOCATION "${ARIADNE_LABELLING_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES
                "${ARIADNE_LABELLING_INCLUDE_PARENT_DIR};${ARIADNE_LABELLING_INCLUDE_DIR}"
            INTERFACE_LINK_LIBRARIES "Threads::Threads"
        )
    endif()
endif()
