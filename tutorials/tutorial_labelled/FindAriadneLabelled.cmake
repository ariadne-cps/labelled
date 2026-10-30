find_library(ARIADNE_LABELLED_LIBRARY NAMES ariadne-labelled)
find_path(ARIADNE_LABELLED_INCLUDE_DIR ariadne-labelled.hpp
          PATH_SUFFIXES ariadne-labelled)

find_package(Threads REQUIRED)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AriadneLabelled DEFAULT_MSG
    ARIADNE_LABELLED_LIBRARY
    ARIADNE_LABELLED_INCLUDE_DIR
)

if(AriadneLabelled_FOUND)
    get_filename_component(ARIADNE_LABELLED_INCLUDE_PARENT_DIR
        "${ARIADNE_LABELLED_INCLUDE_DIR}" DIRECTORY)
    if(NOT TARGET AriadneLabelled::ariadne-labelled)
        add_library(AriadneLabelled::ariadne-labelled UNKNOWN IMPORTED)
        set_target_properties(AriadneLabelled::ariadne-labelled PROPERTIES
            IMPORTED_LOCATION "${ARIADNE_LABELLED_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES
                "${ARIADNE_LABELLED_INCLUDE_PARENT_DIR};${ARIADNE_LABELLED_INCLUDE_DIR}"
            INTERFACE_LINK_LIBRARIES "Threads::Threads"
        )
    endif()
endif()
