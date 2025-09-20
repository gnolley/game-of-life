#include <catch2/catch_test_macros.hpp>
#include "GameFrame.h"
#include "TestUtils.h"


TEST_CASE("Add 1 Cell to Frame", "Add Cells")
{
	GoL::GameFrame frame{};

	frame.set_cell(0, 0);

	REQUIRE(frame.cell_count() == 1);
	REQUIRE(TestUtils::is_cell_alive(frame, 0, 0) == true);
}

TEST_CASE("Co-ordinates Limit Testing", "Add Cells")
{
	GoL::GameFrame frame{};

	frame.set_cell(std::numeric_limits<std::int64_t>::max(), std::numeric_limits<std::int64_t>::min());
	frame.set_cell(std::numeric_limits<std::int64_t>::max() + 1, std::numeric_limits<std::int64_t>::min() - 1); // intentionally overflow the integers

	REQUIRE(frame.cell_count() == 2);
	REQUIRE(TestUtils::is_cell_alive(frame, std::numeric_limits<std::int64_t>::max(), std::numeric_limits<std::int64_t>::min()) == true);
	REQUIRE(TestUtils::is_cell_alive(frame, std::numeric_limits<std::int64_t>::max() + 1, std::numeric_limits<std::int64_t>::min() - 1) == true);
}

TEST_CASE("Clear Frame one 3 Cells", "Clearing Cells")
{
	GoL::GameFrame frame{};

	frame.set_cell(0, 0);
	frame.set_cell(100, 100);
	frame.set_cell(-100,-100);

	CHECK(frame.cell_count() == 3);

	frame.clear();

	REQUIRE(frame.cell_count() == 0);
}