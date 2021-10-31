#include <iostream>
#include <array>
#include <string>

#include "Zinet/Core/ZtFile.h"

#include "Zinet/GraphicLayer/ZtWindow.h"
#include "Zinet/GraphicLayer/ZtShader.h"
#include "Zinet/GraphicLayer/ZtVertex.h"
#include "Zinet/GraphicLayer/ZtProgram.h"
#include "Zinet/GraphicLayer/ZtVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtElementBuffer.h"
#include "Zinet/GraphicLayer/ZtVertexArray.h"
#include "Zinet/GraphicLayer/ZtTexture.h"

#include <GLFW/glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ZtVertexArray VAO;
ZtVertexBuffer VBO;
ZtElementBuffer EBO;
ZtProgram Program;
ZtTexture Texture0;
ZtTexture Texture1;

void ProcessInput(ZtWindow& Window);

void Rendering(ZtWindow& Window);

int main()
{
    ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("Main");

    ZtWindow Window;
    Window.CreateWindow();
    Window.InitStb();

    GLFWwindow* WindowPointer = Window.GetInternalWindow();

    // Fix problem with not valid vertices positions
    int Width, Height;
    glfwGetFramebufferSize(WindowPointer, &Width, &Height);
    Window.SetViewport(0, 0, Width, Height);
    // End Fix

    Window.BindFramebufferSizeCallback();

    Window.SetClearColor(0.1f, 0.1f, 0.1f, 1.f);

    ZtFileFinder FileFinder;
    ZtFileFinder::Path RootPath = FileFinder.CurrentProjectRootPath();

    ZtShader VertexShader;
    VertexShader.Create(ZtShaderType::Vertex);
    ZtFileFinder::Path VertexShaderFilePath = RootPath / "Shaders" / "shader.vert";
    VertexShader.LoadFromFile(VertexShaderFilePath.string());
    VertexShader.Compile();

    unsigned int VertexShaderID = VertexShader.GetID();

    bool VertexShaderCompileStatus = VertexShader.CompileStatus();
    if (!VertexShaderCompileStatus)
    {
        std::cout << "Invalid Vertex Shader" << std::endl;
        std::string Message = VertexShader.CompileErrorMessage();
        std::cout << Message << '\n';
    }

    ZtShader FragmentShader;
    FragmentShader.Create(ZtShaderType::Fragment);
    ZtFileFinder::Path FragmentShaderFilePath = RootPath / "Shaders" / "shader.frag";
    FragmentShader.LoadFromFile(FragmentShaderFilePath.string());
    FragmentShader.Compile();

    unsigned int FragmentShaderID = FragmentShader.GetID();

    bool FragmentShaderCompileStatus = FragmentShader.CompileStatus();
    if (!FragmentShaderCompileStatus)
    {
        std::cout << "Invalid Fragment Shader" << std::endl;
        std::string Message = FragmentShader.CompileErrorMessage();
        std::cout << Message << '\n';
    }

    Program.Create();
    Program.AttachShader(VertexShader);
    Program.AttachShader(FragmentShader);
    Program.Link();

    if (!Program.IsValid())
    {
        std::string InfoLog = Program.InfoLog();
        std::cout << "Invalid program" << std::endl;
        std::cout << InfoLog << std::endl;
    }

    VAO.Generate();
    VBO.Generate();
    EBO.Generate();

    VAO.Bind();

    std::vector<ZtVertex> Vertices {
        {{ 0.5f,   0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 1.0f, 1.0f}}, // top right
        {{ 0.5f,  -0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 1.0f, 0.0f}}, // bottom right
        {{ -0.5f, -0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 0.0f, 0.0f}}, // bottom left
        {{ -0.5f,  0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 0.0f, 1.0f}}  // top left
    };

    std::array<unsigned int, 6> Indices {
        0, 1, 3,
        1, 2, 3
    };

    Texture0.Generate();
    Texture0.Bind();
    ZtFileFinder::Path TexturePath = RootPath / "Textures" / "wall.jpg";
    Texture0.LoadFromFile(TexturePath);
    Texture0.GenerateMipmap();

    VBO.Bind();
    VBO.SetData(Vertices, ZtBufferUsage::Static);

    EBO.Bind();
    EBO.SetData(Indices, ZtBufferUsage::Static);

    // Vertices Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 * sizeof(float)) + (4 * sizeof(float)) + (2 * sizeof(float)), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertices Colors
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, (3 * sizeof(float)) + (4 * sizeof(float)) + (2 * sizeof(float)), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Vertices Texture Coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (3 * sizeof(float)) + (4 * sizeof(float)) + (2 * sizeof(float)), (void*)((3 * sizeof(float)) + (4 * sizeof(float))));
    glEnableVertexAttribArray(2);

    Program.Use();

    VertexShader.Delete();
    FragmentShader.Delete();

    while (!glfwWindowShouldClose(WindowPointer))
    {
        ProcessInput(Window);

        Rendering(Window);
    }

    VAO.Delete();
    EBO.Delete();
    VBO.Delete();
    Texture0.Delete();

    Program.Delete();

    return 0;
}

void ProcessInput(ZtWindow& Window)
{
    // Should be transformed to something like ZtEvent
    GLFWwindow* WindowPointer = Window.GetInternalWindow();

    if (glfwGetKey(WindowPointer, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(WindowPointer, true);
    else if(glfwGetKey(WindowPointer, GLFW_KEY_F1) == GLFW_PRESS)
        ZtGLContext::FillMode();
    else if (glfwGetKey(WindowPointer, GLFW_KEY_F2) == GLFW_PRESS)
        ZtGLContext::PolygonOnlyMode();
    else if (glfwGetKey(WindowPointer, GLFW_KEY_F3) == GLFW_PRESS)
        ZtGLContext::PointsMode();

    glfwPollEvents();
    //


}

void Rendering(ZtWindow& Window)
{
    Window.Clear();

    float timeValue = static_cast<float>(glfwGetTime());
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(Program.GetID(), "OurColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    EBO.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    Window.SwapBuffers();
}