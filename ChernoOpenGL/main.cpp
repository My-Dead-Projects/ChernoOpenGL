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
    uint vbo = createAndBindBuffer(GL_ARRAY_BUFFER,
                                   12 * sizeof(float),
                                   points,
                                   GL_STATIC_DRAW);
    // Create and bind vertex array object
    createAndBindVAO(vbo);
    
    // Create and bind index buffer object
    // Note: IBO must be created _after_ VAO.
    createAndBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
                                   6 * sizeof(uint),
                                   indices,
                                   GL_STATIC_DRAW);
    
    Shader shader("Resources/BasicShaders.glsl");
    
    shader.use();
    
    while(!window.shouldClose()) {
        GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        
        GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        
        glfwPollEvents();
        window.swapBuffers();
    }
    
    window.terminate();
    
    return 0;
}

