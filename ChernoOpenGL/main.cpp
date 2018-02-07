#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include "FileUtils.h"
#include "Shaders.h"
#include "Constants.h"
#include "Window.h"
using namespace std;
#define GL(x) GLClearError(); x; GLLog(#x, __FILE__, __LINE__);

static void GLClearError()
{
    while (glGetError());
}

static void GLLog(const char* func, const char* file, int line)
{
    while (auto error = glGetError())
    {
        cout << endl << "[OpenGL Error] 0x" << hex << error << dec << endl
             << func << endl <<file << ":" << line << endl;
    }
}

int main() {
    
    Window window;
    Error error = window.create(640, 480, "Hello Triangle");
    
    if (error)
    {
        cerr << "Error: " << error.getMessage() << endl;
    }
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    
    GL(glEnable(GL_DEPTH_TEST));
    // depth-testing interprets a smaller value as "closer"
    GL(glDepthFunc(GL_LESS));
    
    float points[] = {
        -.5, -.5,
         .5, -.5,
         .5,  .5,
        -.5,  .5,
    };
    
    uint indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    uint vertexBufferObject = 0;
    GL(glGenBuffers(1, &vertexBufferObject));
    GL(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject));
    GL(glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW));
    
    uint vertexArrayObject = 0;
    GL(glGenVertexArrays(1, &vertexArrayObject));
    GL(glBindVertexArray(vertexArrayObject));
    GL(glEnableVertexAttribArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject));
    GL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL));
    
    // Note: IBO must be created _after_ VAO.
    uint indexBufferObject = 0;
    GL(glGenBuffers(1, &indexBufferObject));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject));
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), indices, GL_STATIC_DRAW));
    
    auto sources = file_utils::readShaderSource("Resources/BasicShaders.glsl");
    
    Shader shader("Resources/BasicShaders.glsl");
    
    shader.use();
    
    GL(glBindVertexArray(vertexArrayObject));
    
    while(!window.shouldClose()) {
        GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        
        GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        //GL(glDrawArrays(GL_TRIANGLES, 0, 3));
        
        glfwPollEvents();
        window.swapBuffers();
    }
    
    window.terminate();
    
    return 0;
}

