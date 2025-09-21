#pragma once
#include <filesystem>

namespace GoL
{
	class Shader
	{
	public:
		Shader() = default;
	    Shader(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path);

		void bind() const;
		void set_float(const std::string& name, float f) const;

	private:
	    void check_compile_errors(unsigned int shader) const;
	    void check_link_errors(unsigned int shader) const;

		unsigned int id {};
	};
}