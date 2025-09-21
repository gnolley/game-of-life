#include "ComputeShader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <format>

#include "glad/gl.h"

namespace GoL
{
    ComputeShader::ComputeShader(const std::filesystem::path& file_path)
    {
        std::filesystem::path path = std::filesystem::current_path() / file_path;
        std::ifstream input(path, std::ifstream::in);

        std::stringstream ss{};
        ss << input.rdbuf();
        std::string code = ss.str();

        const char* cShaderCode = code.c_str();
        unsigned int compute;

        compute = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(compute, 1, &cShaderCode, NULL);
        glCompileShader(compute);
        check_compile_errors(compute);

        id = glCreateProgram();
        glAttachShader(id, compute);
        glLinkProgram(id);
        check_link_errors(id);

        glDeleteShader(compute);
    }

    void ComputeShader::bind() const
    {
        glUseProgram(id);
    }

    void ComputeShader::set_float(const std::string& name, float f) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), f);
    }

    void ComputeShader::check_compile_errors(GLuint shader) const
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

    void ComputeShader::check_link_errors(GLuint shader) const
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
