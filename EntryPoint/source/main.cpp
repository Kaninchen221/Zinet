#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>

std::string VertexShader = "\
#version 330 core\
layout(location = 0) in vec3 aPos;\
\
void main()\
{\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\
}\
";

std::array<float, 9u> Vertices = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height);

void ProcessInput(GLFWwindow* Window);

void Rendering(GLFWwindow* Window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* Window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(Window, FramebufferSizeCallback);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices.data()), Vertices.data(), GL_DYNAMIC_DRAW);

    unsigned int VertexShader;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &VertexShader.c_str(), NULL);
    glCompileShader(VertexShader);

    while (!glfwWindowShouldClose(Window))
    {
        ProcessInput(Window);

        Rendering(Window);
    }

    glfwTerminate();
    return 0;
}

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}

void ProcessInput(GLFWwindow* Window)
{
    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(Window, true);

    glfwPollEvents();
}

void Rendering(GLFWwindow* Window)
{
    glClear(GL_COLOR_BUFFER_BIT);



    glfwSwapBuffers(Window);
}