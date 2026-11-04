if(NOT TARGET expression_set)
    ariadne_add_submodule(expression-set)
endif()

if(NOT TARGET drawing)
    ariadne_add_submodule(drawing)
endif()

# Use the Testing submodule only for test targets.
if(NOT TARGET ariadne-testing)
    ariadne_add_submodule(testing)
endif()
