#ifndef GLError_h
#define GLError_h

#include <iostream>
#define GL(x)\
gl_error::GLClearError();\
x;\
gl_error::GLLog(#x, __FILE__, __LINE__);

namespace gl_error {
    void GLClearError()
    {
        while (glGetError());
    }
    
    void GLLog(const char* func, const char* file, int line)
    {
        while (auto error = glGetError())
        {
            std::cout
            << std::endl << "[OpenGL Error] 0x"
            << std::hex << error << std::dec << std::endl
            << func << std::endl
            << file << ":" << line << std::endl;
        }
    }
}

#endif
