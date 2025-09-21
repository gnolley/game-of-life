#include "GameFrameBuffer.h"
#include "glad/gl.h"
#include <algorithm>

namespace GoL
{
	GameFrameBuffer::GameFrameBuffer(std::int64_t buffer_width, std::int64_t buffer_height, 
		std::int64_t buffer_offset_x, std::int64_t buffer_offset_y)
			: buffer_width(buffer_width), buffer_height(buffer_height),
			buffer_offset_x(buffer_offset_x), buffer_offset_y(buffer_offset_y)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
		//glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(int) * 1000, 0, GL_DYNAMIC_READ);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, id);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void GameFrameBuffer::update_buffer(const GameFrame& frame)
	{
		packed_cells.clear();
		for (const Cell& cell : frame)
		{
			if (is_cell_in_buffer_window(cell))
			{
				packed_cells.push_back(static_cast<int>(cell.x - buffer_offset_x));
				packed_cells.push_back(static_cast<int>(cell.y - buffer_offset_y));
			}
		}

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, id);
		glBufferData(GL_SHADER_STORAGE_BUFFER, packed_cells.size() * sizeof(int), packed_cells.data(), GL_DYNAMIC_READ);
		//glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, static_cast<unsigned long>(packed_cells.size() * sizeof(int) * 2), );
	}

	void GameFrameBuffer::bind(unsigned int bind_index) const
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bind_index, id);
	}

	int GameFrameBuffer::num_cells_packed() const
	{
		return static_cast<int>(packed_cells.size()) * 2;
	}

	bool GameFrameBuffer::is_cell_in_buffer_window(const Cell& cell) const
	{
		std::int64_t min_x = buffer_offset_x, max_x = buffer_width - buffer_offset_x;
		std::int64_t min_y = buffer_offset_y, max_y = buffer_height - buffer_offset_y;

		return cell.x >= min_x && cell.x <= max_x && cell.y >= min_y && cell.y <= max_y;
	}
}
