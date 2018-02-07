#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include "FileUtils.h"
#include "Shaders.h"
#include "Constants.h"
using namespace std;

int main() {
    
    if (!glfwInit()) {
        cerr << "ERROR: Could not start GLFW3" << endl;
        return 1;
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        cerr << "ERROR: could not open window with GLFW3" << endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    
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
    
    auto sources = file_utils::readShaderSource("Resources/BasicShaders.glsl");
    
    Shader shader("Resources/BasicShaders.glsl");
    
    shader.use();
    
    glBindVertexArray(vertexArrayObject);
    
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}

