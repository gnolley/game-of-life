#include <catch2/catch_test_macros.hpp>
#include "FileReader.h"
#include "TestUtils.h"

TEST_CASE("Read 1 Cell From Stream", "Read File")
{
	GoL::GameFrame frame{};
	std::stringstream ss { "#Life 1.06\n"
								"0 1" };

	GoL::FileReader::LoadFile(frame, ss);

	REQUIRE(frame.cell_count() == 1);
	REQUIRE(TestUtils::is_cell_alive(frame, 0, 1) == true);
}

TEST_CASE("Read 3 Cells From Stream", "Read File")
{
	GoL::GameFrame frame{};
	std::stringstream ss{ "#Life 1.06\n"
								"0 0\n"
								"12345678 12345678\n"
								"-12345678 -12345678"};

	GoL::FileReader::LoadFile(frame, ss);

	REQUIRE(frame.cell_count() == 3);
	REQUIRE(TestUtils::is_cell_alive(frame, 0, 0));
	REQUIRE(TestUtils::is_cell_alive(frame, 12345678, 12345678));
	REQUIRE(TestUtils::is_cell_alive(frame, -12345678, -12345678));
}

TEST_CASE("Fail on Malformed Header", "Read File")
{
	GoL::GameFrame frame{};
	std::stringstream ss{ "Malformed Header\n"
								"0 1\n" };

	REQUIRE_THROWS(GoL::FileReader::LoadFile(frame, ss));
}

TEST_CASE("Fail on Malformed Life Snapshot", "Read File")
{
	GoL::GameFrame frame{};
	std::stringstream ss{ "#Life 1.06\n"
								"word 2\n" };

	REQUIRE_THROWS(GoL::FileReader::LoadFile(frame, ss));
}