#pragma once

namespace GoL
{
	struct Cell
	{
		std::int64_t x, y;

		Cell() = default;
		Cell(std::int64_t x, std::int64_t y) : x(x), y(y)
		{}

		Cell(const Cell& other) = default;
		Cell(Cell&& other) = default;

		Cell& operator=(const Cell& other) = default;
		Cell& operator=(Cell&& other) = default;
		~Cell() = default;

		Cell operator+(const Cell& other) const
		{
			return Cell {
				x + other.x,
				y + other.y
			};
		}

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