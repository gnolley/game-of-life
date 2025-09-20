#pragma once

namespace GoL
{
	struct Cell
	{
		std::int64_t x, y;

		bool operator==(const Cell& other) const
		{
			return x == other.x && y == other.y;
		}
	};
}

namespace std {
	template<>
	struct hash<GoL::Cell> {
		size_t operator()(const GoL::Cell& cell) const
		{
			return cell.x ^ cell.y;
		}
	};
}