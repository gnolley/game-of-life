#include "FileReader.h"

namespace GoL
{
#pragma warning(push)
#pragma warning(disable : 4100) // Disable C4100

	GameFrame FileReader::LoadFile(const std::filesystem::path& path)
	{
		return {};
	}

	void FileReader::SaveFile(const GameFrame& game_frame, const std::filesystem::path& path)
	{
	}

#pragma warning(pop) // Restore previous warning state

}