#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include "FileUtils.h"
#include "Shaders.h"
#include "Constants.h"
#include "Window.h"
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
    
    
    glEnable(GL_DEPTH_TEST);
    // depth-testing interprets a smaller value as "closer"
    glDepthFunc(GL_LESS);
    
    float points[] = {
         0.0,  0.5,  0.0,
         0.5, -0.5,  0.0,
        -0.5, -0.5,  0.0
    };
    
    uint vertexBufferObject = 0;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    
    uint vertexArrayObject = 0;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    auto sources = file_utils::readShaderSource("Resources/BasicShaders.glsl");
    
    Shader shader("Resources/BasicShaders.glsl");
    
    shader.use();
    
    glBindVertexArray(vertexArrayObject);
    
    while(!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
        window.swapBuffers();
    }
    
    window.terminate();
    
    return 0;
}

