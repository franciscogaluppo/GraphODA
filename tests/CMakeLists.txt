SET(TESTS_FOLDER "${PROJECT_SOURCE_DIR}/tests")

# Prepare doctest for other targets to use (https://github.com/onqtam/doctest/blob/master/doc/markdown/build-systems.md)
add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE "${TESTS_FOLDER}/doctest.h")

set(TEST_FILES
        "${TESTS_FOLDER}/TestChordal.cpp")

# Make test executable
add_executable(tests $<TARGET_OBJECTS:common> ${TEST_FILES} "${TESTS_FOLDER}/main.cpp")
target_link_libraries(tests doctest tgui sfml-graphics sfml-window sfml-system)
add_test(NAME Unit_Tests COMMAND tests)