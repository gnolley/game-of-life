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


	private:
		std::unordered_set<Cell> frame_cells {};
	};

}
