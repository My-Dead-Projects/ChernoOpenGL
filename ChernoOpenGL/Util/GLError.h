#ifndef GLError_h
#define GLError_h

#include <iostream>
#define GL(x)\
gl_error::GLClearError();\
x;\
gl_error::GLLog(#x, __FILE__, __LINE__);

namespace gl_error {
    void GLClearError();
    
    void GLLog(const char* func, const char* file, int line);
}

#endif
