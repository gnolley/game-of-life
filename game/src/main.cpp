#include <iostream>
#include <thread>

#include "FileReader.h"
#include <CLI/CLI.hpp>

#include "Simulation.h"
#include "../../renderer/includes/Renderer.h"

void simulation_loop(GoL::Simulation& simulation, GoL::Renderer renderer, int max_ticks)
{
	// render the initial frame before simulation
	renderer.render(simulation.get_current_frame());

	int ticks = 0;
	auto next_sim_tick = std::chrono::system_clock::now() + std::chrono::milliseconds(500);
	while (ticks < max_ticks && simulation.get_current_frame().cell_count() > 0 || renderer.window_open())
	{
		if (std::chrono::system_clock::now() < next_sim_tick)
		{
			renderer.render(simulation.get_current_frame());
			continue;
		}

		++ticks;
		simulation.tick();
		renderer.render(simulation.get_current_frame());
		next_sim_tick = std::chrono::system_clock::now() + std::chrono::milliseconds(150);
	}

	std::cout << std::format("Finished simulating after {} ticks\n", ticks);
}

int main(int argc, char** argv)
{
	CLI::App gol_app{ "A game of life in 64-bits!" };
	argv = gol_app.ensure_utf8(argv);

	std::string life_file = "default";
	gol_app.add_option("-f,--file", life_file, "Path to the life 1.06 file you would like to load.");

	int num_ticks = 100;
	gol_app.add_option("-t, --ticks", num_ticks, "Number of ticks to simulate. Default 100.");

	CLI11_PARSE(gol_app, argc, argv);

	if (life_file == "default")
	{
		std::cout << "No life file given. Enter Relative File Path:\n";
		std::cin >> life_file;
	}

	GoL::GameFrame initial_frame{};
	std::filesystem::path relative{ life_file };
	std::filesystem::path life_file_path = std::filesystem::current_path() / relative;

	if (is_regular_file(life_file_path) == false)
	{
		std::cerr << std::format("Invalid path: {}", life_file_path.string());
		return 2;
	}

	GoL::FileReader::LoadFile(initial_frame, life_file_path);
	std::cout << std::format("Loaded snapshot with {} cells.\n", initial_frame.cell_count());

	GoL::Renderer renderer{};
	renderer.init_renderer();

	GoL::Simulation simulation(std::move(initial_frame));
	simulation_loop(simulation, renderer, num_ticks);
}
