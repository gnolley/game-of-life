#pragma once
#include "GameFrame.h"
#include <filesystem>

namespace GoL
{
	class FileReader
	{
	public:
		static GameFrame LoadFile(const std::filesystem::path& path);
		static void SaveFile(const GameFrame& game_frame, const std::filesystem::path& path);
	};
}