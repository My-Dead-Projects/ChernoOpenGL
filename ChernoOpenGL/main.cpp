#define GLEW_STATIC
#include <GL/glew.h>
#include "Constants.h"
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "GLError.h"
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
	GL(auto renderer = glGetString(GL_RENDERER));
	GL(auto version = glGetString(GL_VERSION));
    cout << endl << endl
    << "Renderer: " << renderer << endl
    << "OpenGL version supported: " << version << endl;
    
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
    
    BufferObject vbo;
    vbo.create(GL_ARRAY_BUFFER, 8 * sizeof(float), points, GL_STATIC_DRAW);
    vbo.bind();
    
	VertexArrayObject vao;
	vao.create(0, 2, GL_FLOAT, false, 0, vbo);
    
    BufferObject ibo;
    ibo.create(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), indices, GL_STATIC_DRAW);
    ibo.bind();
    
    Shader shader;
    shader.compileShaders("./Shaders.glsl");
    shader.bind();
    
	GL(glBindVertexArray(vao.getObjectID()));
    
    while(!window.shouldClose()) {
		GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        
		GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        
        glfwPollEvents();
        window.swapBuffers();
    }
    
    window.terminate();
    return 0;
}
