#pragma once

struct GLFWwindow;

namespace GoL
{
	class Renderer
	{
	public:

		void init_renderer();
		void init_window();

		void render();

	private:
		GLFWwindow* window;
	};
}