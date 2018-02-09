#ifndef Window_h
#define Window_h

#include <memory>
#include <GLFW/glfw3.h>
#include "Error.h"

class Window {
private:
    GLFWwindow* m_window;
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
        
        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_window)
        {
            glfwTerminate();
            return Error("Could not open window with GLFW3");
        }
        glfwMakeContextCurrent(m_window);
        
        return Error::OK();
    }
    
    bool shouldClose()
    {
        return glfwWindowShouldClose(m_window);
    }
    
    void swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
    
    void terminate()
    {
        glfwTerminate();
    }
};

#endif
