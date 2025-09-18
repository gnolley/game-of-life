set(SIM_SRC
	"gol_simulation.cpp"
)

set(SIM_INCLUES
	"${SIM_DIR}/includes"
	${SHARED_INCLUDES}
)

add_library(${SIM_TARGET} STATIC ${SIM_SRC})
target_include_directories(${SIM_TARGET} PUBLIC "${SIM_DIR}/includes")

setup_target(${SIM_TARGET}) # sets warnings / optimisation