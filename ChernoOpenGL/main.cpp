#define GLEW_STATIC
#include <GL/glew.h>
#include "Constants.h"
#include "Window.h"
#include "Shader.h"
#include <iostream>

using namespace std;

int main() {
    
    Window window;
    Error e = window.create(640, 480, "Hello Triangle");
    if (e) {
        cerr << e.message() << endl;
        return 1;
    }
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    // get version info
    auto renderer = glGetString(GL_RENDERER);
    auto version = glGetString(GL_VERSION);
    cout << endl << endl
    << "Renderer: " << renderer << endl
    << "OpenGL version supported: " << version << endl;
    
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
    
    Shader shader;
    shader.compileShaders("./Shaders.glsl");
    shader.bind();
    
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
