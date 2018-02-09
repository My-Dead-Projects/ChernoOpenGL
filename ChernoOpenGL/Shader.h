#ifndef Shader_h
#define Shader_h

#include "Constants.h"
#include <string>

class Shader {
private:
    uint m_shaderProgram;
public:
    void compileShaders(const std::string& sourcePath);
    void bind();
    void unbind();
};

#endif
