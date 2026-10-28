if(NOT TARGET expression_set)
    ensure_submodule_initialized(expression-set)
    add_subdirectory(expression-set)
endif()

if(NOT TARGET drawing)
    ensure_submodule_initialized(drawing)
    add_subdirectory(drawing)
endif()
