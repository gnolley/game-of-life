#include <catch2/catch_test_macros.hpp>
#include "GameFrame.h"
#include "Simulation.h"


TEST_CASE("Simulate 1 Cell Dying", "Simulate Cells")
{
	GoL::GameFrame initial_frame{};
	initial_frame.set_cell(0, 0);

	GoL::Simulation simulation(std::move(initial_frame));
	simulation.tick();

	auto new_frame = simulation.get_current_frame();
	REQUIRE(new_frame.cell_count() == 0);
	REQUIRE(new_frame.get_cell(0, 0) == false);
}

TEST_CASE("Simulate 3 Cells to 1 Cell", "Simulate Cells")
{
	GoL::GameFrame initial_frame{};
	initial_frame.set_cell(0, 1);
	initial_frame.set_cell(-1, 0);
	initial_frame.set_cell(1, 0);

	GoL::Simulation simulation(std::move(initial_frame));
	simulation.tick();

	auto new_frame = simulation.get_current_frame();
	REQUIRE(new_frame.cell_count() == 1);
	REQUIRE(new_frame.get_cell(0, 0) == true);
}

TEST_CASE("Simulate Complex Behaviour -> 5->8->4->0", "Simulate Cells")
{
	GoL::GameFrame initial_frame{};
	initial_frame.set_cell(0, 0);
	initial_frame.set_cell(0, 1);
	initial_frame.set_cell(-1, 0);
	initial_frame.set_cell(1, 0);
	initial_frame.set_cell(0, -1);

	GoL::Simulation simulation(std::move(initial_frame));

	simulation.tick();
	REQUIRE(simulation.get_current_frame().cell_count() == 8);

	simulation.tick();
	REQUIRE(simulation.get_current_frame().cell_count() == 4);

	simulation.tick();
	REQUIRE(simulation.get_current_frame().cell_count() == 0);
}