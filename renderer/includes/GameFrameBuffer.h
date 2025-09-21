#pragma once
#include "GameFrame.h"

namespace GoL
{

	class GameFrameBuffer {
	public:
		GameFrameBuffer() = default;
		GameFrameBuffer(std::int64_t buffer_width, std::int64_t buffer_height, std::int64_t buffer_offset_x, std::int64_t buffer_offset_y);

		void update_buffer(const GameFrame& frame);
		void bind(unsigned int bind_index) const;
		int num_cells_packed() const;
	private:
		bool is_cell_in_buffer_window(const Cell& cell) const;

		unsigned int id {};
		std::vector<int> packed_cells {};
		std::int64_t buffer_width{}, buffer_height{}, buffer_offset_x{}, buffer_offset_y{};
	};



}