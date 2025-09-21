#pragma once
#include <vector>

namespace GoL
{
	class Quad
	{
	public:
		Quad() = default;
		Quad(std::vector<float> vertex_attributes);

		void bind() const;
	private:
		unsigned int vao, vbo;
	};
}