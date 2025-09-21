#include "Simulation.h"

namespace GoL
{
	const Cell ADJACENT_CELL_MATRIX[8] = {
		{-1, 1},
		{0, 1},
		{1, 1},
		{-1, 0},
		{1, 0},
		{-1, -1},
		{0, -1},
		{1, -1}
	};

	Simulation::Simulation(GameFrame&& initial_frame)
		: buffers{ initial_frame }
	{

		for (int i=1; i< NUM_GAMEFRAME_BUFFERS; ++i)
		{
			buffers[i] = {}; // initialise all needed buffers
		}
	}

	void Simulation::tick()
	{
		++ticks_simulated;
		GameFrame* prev_frame = last_frame();
		GameFrame* next_frame = current_frame();

		open_set.clear();
		closed_set.clear();
		next_frame->clear();

		for (const Cell& cell : *prev_frame)
		{
			open_set.emplace(cell);
		}

		while (open_set.empty() == false)
		{
			Cell cell = *open_set.begin();
			open_set.erase(cell);
			closed_set.emplace(cell);

			std::uint8_t adjacent_cells = 0;
			for (const Cell& offset : ADJACENT_CELL_MATRIX)
			{
				Cell c = cell + offset;
				if (prev_frame->get_cell(c.x, c.y)) ++adjacent_cells;
			}

			if (adjacent_cells == 0) continue; // don't need to place any new cells in open set if there are no adjacent cells.
			if (adjacent_cells == 3)
			{
				next_frame->set_cell(cell.x, cell.y);
			}
			if (adjacent_cells == 2 && prev_frame->get_cell(cell.x, cell.y))
			{
				next_frame->set_cell(cell.x, cell.y);
			}

			for (const Cell& offset : ADJACENT_CELL_MATRIX)
			{
				Cell c = cell + offset;
				if (closed_set.contains(c)) continue;

				open_set.emplace(c);
			}
		}
	}
}
