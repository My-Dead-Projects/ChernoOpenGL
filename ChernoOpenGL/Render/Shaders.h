#ifndef shaders_h
#define shaders_h
#include <string>
#include "Constants.h"

class Shader {
private:
    uint shaderProgram;
public:
    Shader(const std::string& sourcePath);
    
    void use();
    void unbind();
    uint getProgram()
    {
        return shaderProgram;
    }
};

#endif
