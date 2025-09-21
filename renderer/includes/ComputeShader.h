#pragma once
#include <filesystem>

namespace GoL
{
	class ComputeShader
	{
	public:
		ComputeShader() = default;
	    ComputeShader(const std::filesystem::path& file_path);

		void bind() const;
		void set_float(const std::string& name, float f) const;
	private:
	    void check_compile_errors(unsigned int shader) const;
	    void check_link_errors(unsigned int shader) const;

	    unsigned int id{};
	};
}