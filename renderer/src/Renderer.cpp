#include "Renderer.h"

#include <iostream>
#include <ostream>

#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

// =================================================
//
// Note: This is a light-weight renderer, made quickly. It won't look pretty.
//
// =================================================

namespace GoL
{
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    Renderer::~Renderer()
    {
        glfwTerminate();
    }

	void Renderer::init_renderer()
	{
		init_window();
	}

#pragma warning(push)
#pragma warning(disable : 4100) // Disable C4100
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
#pragma warning(pop) // Restore previous warning state


	void Renderer::init_window()
	{
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game of Life", NULL, NULL);
        if (!window)
        {
            std::cerr << "Failed to create window\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        gladLoadGL(glfwGetProcAddress);
        glfwSwapInterval(1);
	}

	void Renderer::render()
	{
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
	}
}
