#include "Shaders.h"

#include "FileUtils.h"
#include <GL/glew.h>
#include <iostream>
using namespace std;

uint compileShader(const string& source, uint type)
{
    uint id = glCreateShader(type);
    auto src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        cerr << "Failed to compile "
        << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
        << " shader" << endl
        << message << endl;
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

uint createShaders(const string& vertexShader, const string& fragmentShader)
{
    uint program = glCreateProgram();
    
    uint vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    uint fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteProgram(vs);
    glDeleteProgram(fs);
    
    return program;
}

Shader::Shader(const string& sourcePath)
{
    auto source = file_utils::readShaderSource(sourcePath);
    
    shaderProgram = createShaders(source.vertexSource, source.fragmentSource);
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}
