if(NOT TARGET expression_set)
    ariadne_add_submodule(expression-set)
endif()

if(NOT TARGET drawing)
    ariadne_add_submodule(drawing)
endif()

# Temporary: paving remains a direct dependency of legacy labelled adapters.
# The standalone Drawing dependency must never import paving.
if(NOT TARGET paving)
    ariadne_add_submodule(paving)
endif()

