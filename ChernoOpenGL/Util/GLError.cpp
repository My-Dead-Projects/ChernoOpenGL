#include "GLError.h"
#include <iostream>
#include <GL/glew.h>
using namespace std;

void gl_error::GLClearError()
{
    while (glGetError());
}

void gl_error::GLLog(const char* func, const char* file, int line)
{
    while (auto error = glGetError())
    {
        cout
        << endl << "[OpenGL Error] 0x"
        << hex << error << dec << endl
        << func << endl
        << file << ":" << line << endl;
    }
}
