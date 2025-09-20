#pragma once
#include <cstdint>
#include <unordered_set>
#include "Cell.h"

namespace GoL
{

	class GameFrame
	{
	public:
		std::uint32_t cell_count() const;
		bool get_cell(std::int64_t x, std::int64_t y) const;

		void set_cell(std::int64_t x, std::int64_t y);
		void clear();

		using iterator = std::unordered_set<Cell>::iterator;
		using const_iterator = std::unordered_set<Cell>::const_iterator;

		iterator begin() { return frame_cells.begin(); }
		const_iterator begin() const { return frame_cells.begin(); }

		iterator end() { return frame_cells.end(); }
		const_iterator end() const { return frame_cells.end(); }

	private:
		std::unordered_set<Cell> frame_cells {};
	};

}
