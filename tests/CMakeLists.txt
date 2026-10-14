include(CTest)

set(UNIT_TESTS
    test_set
    test_point_curve
    test_figure
)

foreach(TEST ${UNIT_TESTS})
    add_executable(${TEST} ${TEST}.cpp)
    target_link_libraries(${TEST} ariadne-labelling labelling)
    add_test(NAME ${TEST} COMMAND $<TARGET_FILE:${TEST}>)
    set_property(TEST ${TEST} PROPERTY LABELS "labelling")
endforeach()

add_custom_target(tests)
add_dependencies(tests ${UNIT_TESTS})
