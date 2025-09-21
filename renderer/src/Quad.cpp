#include "Quad.h"
#include "glad/gl.h"

namespace GoL
{
	Quad::Quad(std::vector<float> vertex_attributes)
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,  static_cast<long long>(vertex_attributes.size() * sizeof(float)), 
			vertex_attributes.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	void Quad::bind() const
	{
		glBindVertexArray(vao);
	}
}
