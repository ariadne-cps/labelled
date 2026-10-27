if(NOT TARGET symbolic)
    ensure_submodule_initialized(symbolic)
    add_subdirectory(symbolic)
endif()

if(NOT TARGET drawing)
    ensure_submodule_initialized(drawing)
    add_subdirectory(drawing)
endif()
