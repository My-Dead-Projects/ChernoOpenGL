#ifndef FileUtils_h
#define FileUtils_h

#include <string>
#include "Constants.h"

namespace file_utils
{
    
    struct ShaderSource
    {
        std::string vertexSource;
        std::string fragmentSource;
    };
    
    ShaderSource readShaderSource(const std::string& path);
};

#endif
