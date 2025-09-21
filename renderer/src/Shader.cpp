#include "Shader.h"

#include <fstream>
#include <sstream>
#include <format>
#include <iostream>

#include "glad/gl.h"

namespace GoL
{

    void LoadFileContents(const std::filesystem::path& file_path, std::string& contents)
    {
        std::filesystem::path path = std::filesystem::current_path() / file_path;
        std::ifstream input(path, std::ifstream::in);

        std::stringstream ss{};
        ss << input.rdbuf();
        input.close();

        contents = ss.str();
    }

    Shader::Shader(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path)
    {
        std::string vertex_string, fragment_string;

        LoadFileContents(vertex_path, vertex_string);
        LoadFileContents(fragment_path, fragment_string);

        const char* vertex_code = vertex_string.c_str();
        const char* fragment_code = fragment_string.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertex_code, NULL);
        glCompileShader(vertex);
        check_compile_errors(vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragment_code, NULL);
        glCompileShader(fragment);
        check_compile_errors(fragment);

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        check_link_errors(id);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::bind() const
    {
        glUseProgram(id);
    }

    void Shader::set_float(const std::string& name, float f) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), f);
    }

    void Shader::check_compile_errors(unsigned int shader) const
    {
        GLint success;
        GLchar infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << std::format("Error compiling compute shader: {}", infoLog);
        }
    }

    void Shader::check_link_errors(unsigned int shader) const
    {
        GLint success;
        GLchar infoLog[1024];

        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << std::format("Error linking compute shader: {}", infoLog);
        }
    }
	
}
