#include <iostream>
#include <array>
#include <string>

#include "Zinet/Core/ZtFile.h"

#include "Zinet/Renderer/ZtWindow.h"
#include "Zinet/Renderer/ZtShader.h"
#include "Zinet/Renderer/ZtVertex.h"
#include "Zinet/Renderer/ZtProgram.h"
#include "Zinet/Renderer/ZtVertexBuffer.h"
#include "Zinet/Renderer/ZtElementBuffer.h"
#include "Zinet/Renderer/ZtVertexArray.h"

#include <GLFW/glfw3.h>

ZtVertexArray VAO;
ZtVertexBuffer VBO;
ZtElementBuffer EBO;
ZtProgram Program;

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

    // Fix problem with not valid vertices positions
    int Width, Height;
    glfwGetFramebufferSize(WindowPointer, &Width, &Height);
    Window.SetViewport(0, 0, Width, Height);

    Window.BindFramebufferSizeCallback();

    Window.SetClearColor(0.1f, 0.1f, 0.1f, 1.f);

    ZtFileFinder FileFinder;
    ZtFileFinder::Path RootPath = FileFinder.CurrentProjectRootPath();

    ZtFile VertexShaderFile;
    ZtFileFinder::Path VertexShaderFilePath = RootPath / "Shaders" / "shader.vert";
    VertexShaderFile.Open(VertexShaderFilePath, ZtFileOpenMode::In);
    std::string VertexShaderFileSource = VertexShaderFile.ReadAll();
    const char* VertexShaderSourceCStr = VertexShaderFileSource.c_str();
    VertexShaderFile.Close();

    ZtShader VertexShader;
    VertexShader.Create(ZtShaderType::Vertex);
    VertexShader.LoadFromCString(VertexShaderSourceCStr);
    VertexShader.Compile();

    unsigned int VertexShaderID = VertexShader.GetID();

    bool VertexShaderCompileStatus = VertexShader.CompileStatus();
    if (!VertexShaderCompileStatus)
    {
        std::string Message = VertexShader.CompileErrorMessage();
        std::cout << Message << '\n';
    }

    ZtFile FragmentShaderFile;
    ZtFileFinder::Path FragmentShaderFilePath = RootPath / "Shaders" / "shader.frag";
    FragmentShaderFile.Open(FragmentShaderFilePath, ZtFileOpenMode::In);
    std::string FragmentShaderFileSource = FragmentShaderFile.ReadAll();
    const char* FragmentShaderSourceCStr = FragmentShaderFileSource.c_str();
    FragmentShaderFile.Close();

    ZtShader FragmentShader;
    FragmentShader.Create(ZtShaderType::Fragment);
    FragmentShader.LoadFromCString(FragmentShaderSourceCStr);
    FragmentShader.Compile();

    unsigned int FragmentShaderID = FragmentShader.GetID();

    bool FragmentShaderCompileStatus = FragmentShader.CompileStatus();
    if (!FragmentShaderCompileStatus)
    {
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
        std::cout << InfoLog << std::endl;
    }

    VAO.Generate();
    VBO.Generate();
    EBO.Generate();

    VAO.Bind();

    std::vector<ZtVertex> Vertices {
        {{ 0.5f, 0.5f, 0.f }},   // top right
        {{ 0.5f, -0.5f, 0.f }},  // bottom right
        {{ -0.5f, -0.5f, 0.f }},  // bottom left
        {{ -0.5f,  0.5f, 0.f }}  // top left
    };

    std::array<unsigned int, 6> Indices {
        0, 1, 3,
        1, 2, 3
    };

    VBO.Bind();
    VBO.SetData(Vertices, ZtBufferUsage::Static);

    EBO.Bind();
    EBO.SetData(Indices, ZtBufferUsage::Static);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

    float timeValue = static_cast<float>(glfwGetTime());
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(Program.GetID(), "ourColor");
    //glUseProgram(Program.GetID());
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    EBO.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    Window.SwapBuffers();
}