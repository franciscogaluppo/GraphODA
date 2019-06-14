SET(TESTS_FOLDER "${PROJECT_SOURCE_DIR}/tests")

# Prepare doctest for other targets to use (https://github.com/onqtam/doctest/blob/master/doc/markdown/build-systems.md)
add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE "${TESTS_FOLDER}/doctest.h")

set(TEST_FILES
	"${TESTS_FOLDER}/TestChordal.cpp"
	"${TESTS_FOLDER}/TestGraph.cpp"
	"${TESTS_FOLDER}/TestGraphGen.cpp"
	"${TESTS_FOLDER}/TestDag.cpp"
	"${TESTS_FOLDER}/TestBipartite.cpp"
	"${TESTS_FOLDER}/TestInterface.cpp"
	"${TESTS_FOLDER}/TestVector.cpp"
    "${TESTS_FOLDER}/TestTree.cpp"
    "${TESTS_FOLDER}/TestRepl.cpp")

# Make test executable
add_executable(tests EXCLUDE_FROM_ALL 
	$<TARGET_OBJECTS:common>
	${TEST_FILES}
	"${TESTS_FOLDER}/main.cpp")
target_link_libraries(tests doctest tgui sfml-graphics sfml-window sfml-system)

# Actually run the tests
add_custom_command(TARGET tests POST_BUILD
	COMMAND "${CMAKE_CURRENT_BINARY_DIR}/tests"
	COMMENT "Executando testes com o doctest.h ..."
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

