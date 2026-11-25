include(CTest)

set(UNIT_TESTS
    test_set
    test_value
    test_augmented_paving
    test_point_curve
    test_figure
)

foreach(TEST ${UNIT_TESTS})
    add_executable(${TEST} ${TEST}.cpp)
    target_include_directories(${TEST} PRIVATE "${PROJECT_SOURCE_DIR}/src")
    target_link_libraries(${TEST} PRIVATE ariadne-labelled labelled ariadne-testing)
    add_test(NAME ${TEST} COMMAND $<TARGET_FILE:${TEST}> --concise --logtonull)
    set_property(TEST ${TEST} PROPERTY LABELS "labelled")
endforeach()

add_custom_target(tests)
add_dependencies(tests ${UNIT_TESTS})
