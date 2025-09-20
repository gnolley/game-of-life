#include <iostream>
#include "FileReader.h"
#include <CLI/CLI.hpp>

#include "Simulation.h"

void simulation_loop(GoL::Simulation& simulation, int max_ticks)
{
	int ticks = 0;
	while (ticks < max_ticks && simulation.get_current_frame().cell_count() > 0)
	{
		++ticks;
		simulation.tick();
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

	GoL::GameFrame frame{};
	std::filesystem::path relative{ life_file };
	std::filesystem::path life_file_path = std::filesystem::current_path() / relative;

	if (std::filesystem::is_regular_file(life_file_path) == false)
	{
		std::cerr << std::format("Invalid path: {}", life_file_path.string());
		return 2;
	}

	GoL::FileReader::LoadFile(frame, life_file_path);
	std::cout << std::format("Loaded snapshot with {} cells.\n", frame.cell_count());

	GoL::Simulation simulation(std::move(frame));
	simulation_loop(simulation, num_ticks);
}
