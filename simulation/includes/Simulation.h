#pragma once
#include <set>

#include "GameFrame.h"

constexpr size_t NUM_GAMEFRAME_BUFFERS = 2;

namespace GoL {
	class Simulation {
	public:
		Simulation(GameFrame&& initial_frame);

		// public const accessor so we can't mess with the simulation data externally
		const GameFrame& get_current_frame() const { return buffers[ticks_simulated % NUM_GAMEFRAME_BUFFERS]; };

		void tick();

	private:
		GameFrame buffers[NUM_GAMEFRAME_BUFFERS];
		std::uint32_t ticks_simulated{0};

		std::unordered_set<Cell> open_set{}, closed_set{};

		GameFrame* current_frame() { return &buffers[ticks_simulated % NUM_GAMEFRAME_BUFFERS]; }
		GameFrame* last_frame() { return &buffers[(ticks_simulated - 1) % NUM_GAMEFRAME_BUFFERS]; }
	};
}