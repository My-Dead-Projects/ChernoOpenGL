#include "Shaders.h"

#include "FileUtils.h"
#include "GLError.h"
#include <iostream>
#include <GL/glew.h>
using namespace std;

uint compileShader(const string& source, uint type)
{
    GL(uint id = glCreateShader(type))
    auto src = source.c_str();
    GL(glShaderSource(id, 1, &src, nullptr))
    GL(glCompileShader(id))
    
    int result;
    GL(glGetShaderiv(id, GL_COMPILE_STATUS, &result))
    
    if (result == GL_FALSE)
    {
        int length;
        GL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length))
        char message[length];
        GL(glGetShaderInfoLog(id, length, &length, message))
        cerr << "Failed to compile "
        << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
        << " shader" << endl
        << message << endl;
        GL(glDeleteShader(id))
        return 0;
    }
    
    return id;
}

uint createShaders(const string& vertexShader, const string& fragmentShader)
{
    GL(uint program = glCreateProgram())
    
    uint vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    uint fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
    
    GL(glAttachShader(program, vs))
    GL(glAttachShader(program, fs))
    GL(glLinkProgram(program))
    GL(glValidateProgram(program))
    GL(glDeleteProgram(vs))
    GL(glDeleteProgram(fs))
    
    return program;
}

Shader::Shader(const string& sourcePath)
{
    auto source = file_utils::readShaderSource(sourcePath);
    
    shaderProgram = createShaders(source.vertexSource, source.fragmentSource);
}

void Shader::use()
{
    GL(glUseProgram(shaderProgram))
}

void Shader::unbind()
{
    GL(glUseProgram(0))
}
