#include <iostream>
#include <thread>

#include "FileReader.h"
#include <CLI/CLI.hpp>

#include "Simulation.h"
#include "../../renderer/includes/Renderer.h"

void simulation_loop(GoL::Simulation& simulation, GoL::Renderer renderer, int max_ticks, int tick_speed)
{
	// render the initial frame before simulation
	renderer.render(simulation.get_current_frame());

	int ticks = 0;
	auto next_sim_tick = std::chrono::system_clock::now() + std::chrono::milliseconds(tick_speed);

	// Simulate while
	//		the window is open
	//		if we're not in endless mode, we haven't exceeded max ticks,
	//		there are cells remaining
	while (renderer.window_open() && 
		(max_ticks == -1 || (max_ticks > 0 && ticks < max_ticks)) && simulation.get_current_frame().cell_count() > 0)
	{
		if (std::chrono::system_clock::now() < next_sim_tick)
		{
			renderer.render(simulation.get_current_frame());
			continue;
		}

		++ticks;
		simulation.tick();
		renderer.render(simulation.get_current_frame());
		next_sim_tick = std::chrono::system_clock::now() + std::chrono::milliseconds(tick_speed);
	}

	std::cout << std::format("Finished simulating after {} ticks\n", ticks);
}

void simulation_headless(GoL::Simulation& simulation, int max_ticks)
{
	if (max_ticks == -1)
	{
		std::cout << "Trying to run endless in headless mode. Defaulting ticks to 1000\n";
		max_ticks = 1000;
	}

	int ticks = 0;
	while (ticks < max_ticks) {
		++ticks;
		simulation.tick();
	}

	std::cout << std::format("Finished simulating after {} ticks\n", ticks);
}

void output_file(const GoL::Simulation& simulation, const std::filesystem::path& output_path)
{
	if (output_path == "default") return;

	std::filesystem::path output_path_absolute = std::filesystem::current_path() / output_path;

	if (exists(output_path_absolute))
	{
		std::cerr << std::format("Output {} is not empty! No output generated\n", output_path_absolute.string());
		return;
	}

	if (is_directory(output_path_absolute) || output_path_absolute.extension() != ".lif")
	{
		std::cerr << std::format("Invalid output path: {}. No output generated\n", output_path_absolute.string());
		return;
	}

	std::cout << std::format("Writing output file to {}.\n", output_path_absolute.string());
	GoL::FileReader::SaveFile(simulation.get_current_frame(), output_path_absolute);
}

int main(int argc, char** argv)
{
	CLI::App gol_app{ "A game of life in 64-bits! Simulate .lif files in the life 1.06 file type.", "Game of Life"};
	gol_app.usage("To use the app, just run it with the below options.");
	argv = gol_app.ensure_utf8(argv);

	std::string life_file = "default";
	std::string output_path = "default";
	int num_ticks = -1;
	int sim_width = 64;
	int sim_height = 64;
	int tick_speed = 150;
	bool headless = false;

	gol_app.add_option("-f,--file", life_file, "Path to the life 1.06 file you would like to load.");
	gol_app.add_option("-o, --output", output_path, "Where to output .lif file after simulation");
	gol_app.add_option("-t, --ticks", num_ticks, "Number of ticks to simulate. -1 will run until window closed.");
	gol_app.add_option("-w, --width", sim_width, "Width of the simulation render in pixels. Default 64.");
	gol_app.add_option("-i, --height", sim_height, "Height of the simulation render in pixels. Default 64.");
	gol_app.add_option("-s, --speed", tick_speed, "Tick speed in milliseconds. Default 500.");
	gol_app.add_flag("-d, --headless", headless, "Whether to run the renderer");

	CLI11_PARSE(gol_app, argc, argv);


	if (life_file == "default")
	{
		std::cout << "No life file given. Enter Relative File Path:\n";
		std::cin >> life_file;
	}

	if (tick_speed <=0)
	{
		std::cout << "Tick speed cannot be lower than 1ms.";
		tick_speed = 1;
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
	GoL::Simulation simulation(std::move(initial_frame));

	if (headless) simulation_headless(simulation, num_ticks);
	else
	{
		renderer.init_renderer(sim_width, sim_height);
		simulation_loop(simulation, renderer, num_ticks, tick_speed);
	}

	output_file(simulation, output_path);
}
