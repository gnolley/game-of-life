set(RENDERER_SRC
	"Renderer.cpp"
)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_library(${RENDERER_TARGET} STATIC ${RENDERER_SRC})
target_link_libraries(${RENDERER_TARGET} PRIVATE ${SHARED_TARGET} ${OPENGL_LIBRARY} glfw)
target_include_directories(${RENDERER_TARGET} PUBLIC "${RENDERER_DIR}/includes")

setup_target(${RENDERER_TARGET}) # sets warnings / optimisation