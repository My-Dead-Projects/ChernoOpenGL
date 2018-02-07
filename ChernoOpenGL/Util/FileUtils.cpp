#include "FileUtils.h"
#include <fstream>
#include <sstream>
using namespace std;
using namespace file_utils;

ShaderSource file_utils::readShaderSource(const string& path)
{
    string line;
    ifstream in(path);
    stringstream vertexStream, fragmentStream;
    string type = "none";
    
    while (getline(in, line))
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
    return { vertexStream.str(), fragmentStream.str() };
}
