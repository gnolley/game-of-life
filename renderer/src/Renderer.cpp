#include "Renderer.h"

#include <iostream>
#include <ostream>

#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "ComputeShader.h"
#include "Shader.h"

// =================================================
//
// Note: This is a light-weight renderer, made quickly. It won't look pretty.
//
// =================================================

namespace GoL
{
    const int SCR_WIDTH = 800;
    const int SCR_HEIGHT = 600;
    const int TEXTURE_WIDTH = 64, TEXTURE_HEIGHT = 64;

	#pragma warning(push)
	#pragma warning(disable : 4100) // Disable C4100
	    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	    {
	        glViewport(0, 0, width, height);
	    }
	#pragma warning(pop) // Restore previous warning state

    Renderer::~Renderer()
    {
        glfwTerminate();
    }

	void Renderer::init_renderer()
	{
		init_window();

        texture_generation_shader = ComputeShader({ "shaders/generate_life_texture.comp" });
        quad_blit_shader = Shader({ "shaders/quad.vert" }, { "shaders/quad.frag" });
        texture = Texture(TEXTURE_WIDTH, TEXTURE_HEIGHT);
        frame_buffer = GameFrameBuffer(TEXTURE_WIDTH, TEXTURE_HEIGHT, -TEXTURE_WIDTH / 2, -TEXTURE_HEIGHT / 2);

        std::vector quad_verts = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };

        quad = Quad(quad_verts);
	}

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

	void Renderer::render(const GameFrame& frame)
	{
        double time = glfwGetTime();
        double delta_time = time - time_last_frame;

        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture.bind();
        texture.clear();
        
        frame_buffer.update_buffer(frame);
        frame_buffer.bind(1);

        texture_generation_shader.bind();
        texture_generation_shader.set_float("t", static_cast<float>(delta_time));

        glDispatchCompute(frame_buffer.num_cells_packed(), 1, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        quad_blit_shader.bind();
        quad.bind();

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
	}

	bool Renderer::window_open()
	{
        return !glfwWindowShouldClose(window);
	}
}
