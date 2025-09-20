set(TEST_SRC 
	"FileReaderTests.cpp"
	"TestUtils.h")

set(TEST_TARGET GoL-Tests)

add_executable(${TEST_TARGET} ${TEST_SRC} "CellTest.cpp")
target_link_libraries(${TEST_TARGET} PUBLIC Catch2::Catch2WithMain ${TEST_GAME_LIBRARY} ${SHARED_TARGET} ${SIM_TARGET})

catch_discover_tests(${TEST_TARGET})