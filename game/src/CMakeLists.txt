set(GAME_SRC "main.cpp"
	"FileReader.cpp"
)

add_executable(${GAME_EXECUTABLE} ${GAME_SRC})
target_include_directories(${GAME_EXECUTABLE} PRIVATE ${GAME_DIR}/includes ${SHARED_INCLUDES})

setup_target(${GAME_EXECUTABLE})