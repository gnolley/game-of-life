set(GAME_SRC "main.cpp"
	"FileReader.cpp"
)

set(GAME_LIBRARIES ${SHARED_TARGET} CLI11::CLI11)

if(BUILD_UNIT_TESTS)
	add_library(${TEST_GAME_LIBRARY} STATIC ${GAME_SRC})
	target_include_directories(${TEST_GAME_LIBRARY} PUBLIC ${GAME_DIR}/includes)
	target_link_libraries(${TEST_GAME_LIBRARY} PUBLIC ${GAME_LIBRARIES})
endif()

add_executable(${GAME_EXECUTABLE} ${GAME_SRC})
target_include_directories(${GAME_EXECUTABLE} PRIVATE ${GAME_DIR}/includes)

find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(${GAME_EXECUTABLE} PRIVATE ${GAME_LIBRARIES})

setup_target(${GAME_EXECUTABLE})