#include "FileReader.h"
#include <fstream>

namespace GoL
{

	constexpr std::streamsize HEADER_LENGTH = 11;
	constexpr std::uint32_t MAX_LINES_READ = 100000; // Avoid infinite loop from corrupted files.

	void FileReader::LoadFile(GameFrame& frame, const std::filesystem::path& path)
	{
		std::ifstream file_stream { path, std::ifstream::in };
		LoadFile(frame, file_stream);
	}

	void FileReader::LoadFile(GameFrame& frame, std::istream& input)
	{
		// Expected header line is #Life 1.06
		char buf[HEADER_LENGTH]{};
		input.getline(buf, HEADER_LENGTH);

		if (strcmp(buf, "#Life 1.06") != 0)
		{
			throw std::runtime_error("Cannot read provided input! Incorrect file type.");
		}

		std::int64_t x, y;
		std::uint32_t control = 0;
		while (input.good())
		{
			input >> x >> y;
			frame.set_cell(x, y );

			if (++control >= MAX_LINES_READ || input.fail())
			{
				throw std::runtime_error(std::format("Error processing life snapshot! Malformed input, or cells exceeding {}.", MAX_LINES_READ));
			}
		}
	}

#pragma warning(push)
#pragma warning(disable : 4100) // Disable C4100

	void FileReader::SaveFile(const GameFrame& game_frame, const std::filesystem::path& path)
	{
	}

#pragma warning(pop) // Restore previous warning state

}
