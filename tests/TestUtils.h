#pragma once
#include "GameFrame.h"

class TestUtils
{
public:
	static bool is_cell_alive(const GoL::GameFrame& frame, std::int64_t cell_x, std::int64_t cell_y) { return frame.get_cell(cell_x, cell_y); } // in case I ever want to change what get_cell returns
};

