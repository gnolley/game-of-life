set(TEST_SRC 
	"test.cpp"
)

set(TEST_TARGET GoL-Tests)

add_executable(${TEST_TARGET} ${TEST_SRC})
target_include_directories(${TEST_TARGET} PRIVATE ${GAME_DIR}/includes ${SHARED_INCLUDES})
target_link_libraries(${TEST_TARGET} PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(${TEST_TARGET})