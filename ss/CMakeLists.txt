if(NOT TARGET symbolic)
    ariadne_add_submodule(symbolic)
endif()

if(NOT TARGET function)
    ariadne_add_submodule(function)
endif()

if(NOT TARGET utility)
    ariadne_add_submodule(utility)
endif()

if(NOT TARGET logging)
    ariadne_add_submodule(logging)
endif()
