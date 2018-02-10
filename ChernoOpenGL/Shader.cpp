#include "Shader.h"

#include <GL/glew.h>
#include "GLError.h"
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
    
    GL(uint vertexShader = glCreateShader(GL_VERTEX_SHADER));
	GL(glShaderSource(vertexShader, 1, &vertexShaderStr, nullptr));
	GL(glCompileShader(vertexShader));
	GL(uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
	GL(glShaderSource(fragmentShader, 1, &fragmentShaderStr, nullptr));
	GL(glCompileShader(fragmentShader));
    
	GL(m_shaderProgram = glCreateProgram());
	GL(glAttachShader(m_shaderProgram, vertexShader));
	GL(glAttachShader(m_shaderProgram, fragmentShader));
	GL(glLinkProgram(m_shaderProgram));
}

void Shader::bind()
{
	GL(glUseProgram(m_shaderProgram));
}

void Shader::unbind()
{
	GL(glUseProgram(0));
}
