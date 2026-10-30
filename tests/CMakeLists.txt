include(CTest)

set(UNIT_TESTS
    test_set
    test_point_curve
    test_figure
)

foreach(TEST ${UNIT_TESTS})
    add_executable(${TEST} ${TEST}.cpp)
    target_link_libraries(${TEST} ariadne-labelled labelled)
    add_test(NAME ${TEST} COMMAND $<TARGET_FILE:${TEST}>)
    set_property(TEST ${TEST} PROPERTY LABELS "labelled")
endforeach()

add_custom_target(tests)
add_dependencies(tests ${UNIT_TESTS})
