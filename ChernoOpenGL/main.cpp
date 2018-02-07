#include <GL/glew.h>
#include <iostream>
#include "FileUtils.h"
#include "Shaders.h"
#include "Constants.h"
#include "Window.h"
#include "Buffers.h"
#include "GLError.h"
using namespace std;

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
    
    // Create and bind vertex buffer object
    uint vbo = createBuffer(GL_ARRAY_BUFFER,
                                   8 * sizeof(float),
                                   points,
                                   GL_STATIC_DRAW);
    bindBuffer(GL_ARRAY_BUFFER, vbo);
    
    // Create and bind vertex array object
    createVertexArrayObject(vbo);
    
    // Create and bind index buffer object
    // Note: IBO must be created _after_ VAO.
    uint ibo = createBuffer(GL_ELEMENT_ARRAY_BUFFER,
                                   6 * sizeof(uint),
                                   indices,
                                   GL_STATIC_DRAW);
    bindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    Shader shader("BasicShaders.glsl");
    
    shader.use();
    
    GL(int location = glGetUniformLocation(shader.getProgram(), "u_color"))
    if (location == -1)
    {
        throw new exception;
    }
    
    
    float r = 0;
    float inc = .05;
    
    while(!window.shouldClose()) {
        GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        
        GL(glUniform4f(location, r, .3, .8, 1.0))
        GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        
        if (r > 1)
            inc = -.05;
        else if (r < 0)
            inc = .05;
        
        r += inc;
        
        glfwPollEvents();
        window.swapBuffers();
    }
    
    window.terminate();
    
    return 0;
}

