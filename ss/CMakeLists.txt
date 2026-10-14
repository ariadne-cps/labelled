if(NOT TARGET symbolic)
    ensure_submodule_initialized(symbolic)
    add_subdirectory(symbolic)
endif()
