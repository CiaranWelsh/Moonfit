include(GoogleTest)

# BINARY: Name of the binary for the test unit you are adding
# LINK_WITH_GOOGLETEST: ON or OFF.
# OUT_VARIABLE: test target will be added into this list
function(add_test_executable BINARY LINK_WITH_GOOGLETEST OUT_VARIABLE)
    add_executable(${BINARY} ${ARGN})

    if (${LINK_WITH_GOOGLETEST})
        target_link_libraries(${BINARY} PRIVATE gtest gtest_main gmock gmock_main)
    endif ()

    target_link_libraries(${BINARY} PRIVATE Moonfit)

    gtest_add_tests(TARGET ${BINARY})


    if ("${${OUT_VARIABLE}}" STREQUAL "")
        set(${OUT_VARIABLE} "${BINARY}" PARENT_SCOPE)
    else ()
        set(${OUT_VARIABLE} "${${OUT_VARIABLE}}" "${BINARY}" PARENT_SCOPE)
    endif ()

endfunction()

set(TestExecutables)

add_test_executable(BuildTheExampleModels ON TestExecutables BuildTheExampleModels.cpp)
target_compile_definitions(BuildTheExampleModels PRIVATE TESTINGMODE)















