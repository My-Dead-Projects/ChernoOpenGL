#include "Shader.h"

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct ShaderSource {
    string vertexShader;
    string fragmentShader;
};

ShaderSource readShaderSource(const string& sourcePath)
{
    stringstream vertexStream, fragmentStream;
    ifstream sourceFile(sourcePath);
    string type, line;
    
    while (getline(sourceFile, line))
    {
        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != string::npos)
            {
                type = "vertex";
            }
            else if (line.find("fragment") != string::npos)
            {
                type = "fragment";
            }
        }
        else // if we don't see #shader
        {
            if (type == "vertex")
            {
                vertexStream << line << "\n";
            }
            else if (type == "fragment")
            {
                fragmentStream << line << "\n";
            }
        }
    }
    
    return {
        move(vertexStream.str().c_str()),
        move(fragmentStream.str().c_str())
    };
}

void Shader::compileShaders(const std::string& sourcePath)
{
    ShaderSource source = readShaderSource(sourcePath);
    
    cout << "Compiling shaders" << endl;
    cout << source.vertexShader << endl;
    cout << source.fragmentShader << endl;
    
    auto vertexShaderStr = source.vertexShader.c_str();
    auto fragmentShaderStr = source.fragmentShader.c_str();
    
    uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderStr, nullptr);
    glCompileShader(vertexShader);
    uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderStr, nullptr);
    glCompileShader(fragmentShader);
    
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
}

void Shader::bind()
{
    glUseProgram(m_shaderProgram);
}

void Shader::unbind()
{
    glUseProgram(0);
}
