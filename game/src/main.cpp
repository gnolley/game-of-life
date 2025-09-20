#include <iostream>
#include "FileReader.h"
#include <CLI/CLI.hpp>


int main(int argc, char** argv)
{
	CLI::App gol_app{ "A game of life in 64-bits!" };
	argv = gol_app.ensure_utf8(argv);

	std::string life_file = "default";
	gol_app.add_option("-f,--file", life_file, "Path to the life 1.06 file you would like to load.");

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
	std::cout << std::format("Loaded snapshot with {} cells.", frame.cell_count());
}