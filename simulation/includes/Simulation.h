#pragma once
#include <set>

#include "GameFrame.h"

constexpr size_t NUM_GAMEFRAME_BUFFERS = 2;

namespace GoL {
	class Simulation {
	public:
		Simulation(GameFrame&& initial_frame);

		void tick();
	};
}