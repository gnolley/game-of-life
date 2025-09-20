#pragma once
#include "GameFrame.h"
#include <filesystem>

namespace GoL
{
	class FileReader
	{
	public:
		static void LoadFile(GameFrame& frame, const std::filesystem::path& path);
		static void LoadFile(GameFrame& frame, std::istream& input);

		static void SaveFile(const GameFrame& game_frame, const std::filesystem::path& path);
	};
}