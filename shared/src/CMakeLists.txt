set(SHARED_SRC
	"GameFrame.cpp"
)

add_library(${SHARED_TARGET} STATIC ${SHARED_SRC})
target_include_directories(${SHARED_TARGET} PUBLIC ${SHARED_DIR}/includes)

setup_target(${SHARED_TARGET})