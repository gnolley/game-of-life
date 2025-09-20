#include "GameFrame.h"

namespace GoL
{

	std::uint32_t GameFrame::cell_count() const
	{
		return static_cast<std::uint32_t>(frame_cells.size());
	}

	bool GameFrame::get_cell(std::int64_t x, std::int64_t y) const
	{
		return frame_cells.contains(Cell {x, y});
	}

	void GameFrame::set_cell(std::int64_t x, std::int64_t y)
	{
		frame_cells.emplace(Cell{ x, y });
	}

	void GameFrame::clear()
	{
		frame_cells.clear();
	}
}
