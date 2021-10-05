#include <iostream>
#include <array>
#include <string>

#include "Zinet/Renderer/ZtWindow.h"
#include "Zinet/Renderer/ZtShader.h"

#include <GLFW/glfw3.h>

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;
unsigned int ShaderProgram;

void ProcessInput(ZtWindow& Window);

void Rendering(ZtWindow& Window);

int main()
{
    ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("Main");

    ZtWindow Window;
    Window.InitGLFW();
    Window.CreateWindow();
    Window.InitGLAD();
    Window.InitOpenGL();

    GLFWwindow* WindowPointer = Window.GetInternalWindow();

    int Width, Height;
    glfwGetFramebufferSize(WindowPointer, &Width, &Height);
    Window.SetViewport(0, 0, Width, Height);

    Window.BindFramebufferSizeCallback();

    Window.SetClearColor(0.1f, 0.1f, 0.1f, 1.f);

  const char *VertexShaderSource =
  "#version 330 core \n"
  "layout(location = 0) in vec3 aPos; \n"
  "out vec4 VertexColor; \n"
  " \n"
  "void main() \n"
  "{ \n"
  "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
  "VertexColor = vec4(0.5, 0.0, 0.0, 1.0); \n"
  "} \n\0";

    ZtShader VertexShader;
    VertexShader.Create(ZtShaderType::Vertex);
    VertexShader.LoadFromCString(VertexShaderSource);
    VertexShader.Compile();

    unsigned int VertexShaderID = VertexShader.GetID();

    bool VertexShaderCompileStatus = VertexShader.CompileStatus();
    if (!VertexShaderCompileStatus)
    {
        std::string Message = VertexShader.CompileErrorMessage();
        std::cout << Message << '\n';
    }

    const char* FragmentShaderSource =
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


    ZtShader FragmentShader;
    FragmentShader.Create(ZtShaderType::Fragment);
    FragmentShader.LoadFromCString(FragmentShaderSource);
    FragmentShader.Compile();

    unsigned int FragmentShaderID = FragmentShader.GetID();

    bool FragmentShaderCompileStatus = FragmentShader.CompileStatus();
    if (!FragmentShaderCompileStatus)
    {
        std::string Message = FragmentShader.CompileErrorMessage();
        std::cout << Message << '\n';
    }

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
    else if(glfwGetKey(WindowPointer, GLFW_KEY_F1) == GLFW_PRESS)
        Window.FillMode();
    else if (glfwGetKey(WindowPointer, GLFW_KEY_F2) == GLFW_PRESS)
        Window.PolygonOnlyMode();
    else if (glfwGetKey(WindowPointer, GLFW_KEY_F3) == GLFW_PRESS)
        Window.PointsMode();

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