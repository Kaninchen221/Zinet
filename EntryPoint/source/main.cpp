#include <iostream>
#include <array>
#include <string>

#include "Zinet/Renderer/ZtWindow.h"

#include <GLFW/glfw3.h>

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;
unsigned int ShaderProgram;

void ProcessInput(ZtWindow& Window);

void Rendering(ZtWindow& Window);

int main()
{

    ZtWindow Window;
    Window.InitGLFW();
    Window.CreateWindow();
    Window.InitGLAD();

    GLFWwindow* WindowPointer = Window.GetInternalWindow();

    int VertexMaxAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &VertexMaxAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << VertexMaxAttributes << std::endl;

    int Width, Height;
    glfwGetFramebufferSize(WindowPointer, &Width, &Height);
    Window.SetViewport(0, 0, Width, Height);

    Window.BindFramebufferSizeCallback();

    Window.SetClearColor(0.1f, 0.1f, 0.1f, 1.f);

  const char *VertexShader =
  "#version 330 core \n"
  "layout(location = 0) in vec3 aPos; \n"
  "out vec4 VertexColor; \n"
  " \n"
  "void main() \n"
  "{ \n"
  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
  "VertexColor = vec4(0.5, 0.0, 0.0, 1.0); \n"
  "} \n\0";

    unsigned int VertexShaderID;
    VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderID, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderID);

    // Log error about compiling shader if any
    {
        int  Success{};
        char InfoLog[512];
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Success);

        if (!Success)
        {
            glGetShaderInfoLog(VertexShaderID, 512, NULL, InfoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << InfoLog << std::endl;
        }
    }
    //

    const char* FragmentShaderCode =
        "#version 330 core \n"
        "out vec4 FragColor; \n"
        "in vec4 VertexColor; \n"
        "uniform vec4 ourColor; \n"
        " \n"
        "void main() \n"
        "{ \n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
        "   FragColor = VertexColor; \n"
        "   FragColor = ourColor; \n"
        "} \n\0";

    unsigned int FragmentShaderID;
    FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderID, 1, &FragmentShaderCode, NULL);
    glCompileShader(FragmentShaderID);

    // Log error about compiling shader if any
    {
        int  Success{};
        char InfoLog[512];
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Success);

        if (!Success)
        {
            glGetShaderInfoLog(FragmentShaderID, 512, NULL, InfoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << InfoLog << std::endl;
        }
    }
    //

    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, VertexShaderID);
    glAttachShader(ShaderProgram, FragmentShaderID);
    glLinkProgram(ShaderProgram);

    // Log error about shader program if any
    {
        int Success{};
        char InfoLog[512];
        glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
        if (!Success) {
            glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
            std::cout << InfoLog << std::endl;
        }
    }
    //

    // VAO decl
    glGenVertexArrays(1, &VAO);

    // VBO decl
    glGenBuffers(1, &VBO);

    // EBO decl
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    float Vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.f, // bottom left
        -0.5f,  0.5f, 0.0f  // top left
    };

    unsigned int Indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(ShaderProgram);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Draw as line

    while (!glfwWindowShouldClose(WindowPointer))
    {
        ProcessInput(Window);

        Rendering(Window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ShaderProgram);

    return 0;
}

void ProcessInput(ZtWindow& Window)
{
    // Should be transformed to something like ZtEvent
    GLFWwindow* WindowPointer = Window.GetInternalWindow();

    if (glfwGetKey(WindowPointer, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(WindowPointer, true);

    glfwPollEvents();
    //


}

void Rendering(ZtWindow& Window)
{
    Window.Clear();

    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(ShaderProgram, "ourColor");
    glUseProgram(ShaderProgram);
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    
    //glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    Window.SwapBuffers();
}