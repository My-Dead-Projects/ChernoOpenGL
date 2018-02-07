#ifndef Window_h
#define Window_h

#include <memory>
#include <GLFW/glfw3.h>
#include "Error.h"

class Window {
private:
    GLFWwindow* window;
public:
    Error create(int width, int height, const char* title)
    {
        if (!glfwInit())
        {
            return Error("Could not start GLFW3");
        }
        
#ifdef __APPLE__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
        
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            return Error("Could not open window with GLFW3");
        }
        glfwMakeContextCurrent(window);
        
        return Error::OK;
    }
    
    bool shouldClose()
    {
        return glfwWindowShouldClose(window);
    }
    
    void terminate()
    {
        glfwTerminate();
    }
};

#endif
