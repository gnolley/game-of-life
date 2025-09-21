#pragma once
#include "ComputeShader.h"
#include "GameFrameBuffer.h"
#include "Quad.h"
#include "Shader.h"
#include "Texture.h"

struct GLFWwindow;

namespace GoL
{
	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer();

		void init_renderer();
		void init_window();

		void render(const GameFrame& frame);
		bool window_open();

	private:
		GLFWwindow* window;

		Texture texture {};
		Quad quad{ };
		ComputeShader texture_generation_shader {};
		Shader quad_blit_shader {};
		GameFrameBuffer frame_buffer{ };

		float time_last_frame {};
	};
}