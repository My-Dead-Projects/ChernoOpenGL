#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
#define uint uint32_t

static uint compileShader(const string& source, uint type)
{
    uint id = glCreateShader(type);
    auto src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Failed to compile "
             << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
             << " shader" << endl
             << message << endl;
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

static uint createShader(const string& vertextShader, const string& fragmentShader)
{
    uint program = glCreateProgram();
    
    uint vs = compileShader(vertextShader, GL_VERTEX_SHADER);
    uint fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteProgram(vs);
    glDeleteProgram(fs);
    
    return program;
}

int main() {
    
    if (!glfwInit()) {
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
    
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }
    
    cout << glGetString(GL_VERSION) << endl;
    
    float positions[] {
        -0.5, -0.5,
         0.0,  0.5,
         0.5, -0.5
    };
    
    uint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    string vertexShader =
    "#version 330 core\n"
    ""
    "layout(location = 0) in vec4 position;"
    ""
    "void main()"
    "{"
    "   gl_Position = position;"
    "}";
    
    string fragmentShader =
    "#version 330 core\n"
    ""
    "layout(location = 0) out vec4 color;"
    ""
    "void main()"
    "{"
    "   color = vec4(1.0, 0.0, 0.0, 1.0);"
    "}";
    
    uint shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);
    
    glClearColor(0.2, 0.3, 03, 1.0);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}

