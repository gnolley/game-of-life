set(SIM_SRC
	"Simulation.cpp"
)

add_library(${SIM_TARGET} STATIC ${SIM_SRC})
target_link_libraries(${SIM_TARGET} PRIVATE ${SHARED_TARGET})
target_include_directories(${SIM_TARGET} PUBLIC "${SIM_DIR}/includes")

setup_target(${SIM_TARGET}) # sets warnings / optimisation