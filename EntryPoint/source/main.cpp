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
#include "Zinet/GraphicLayer/ZtEvent.h"

#include <GLFW/glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

ZtVertexArray VAO;
ZtVertexBuffer VBO;
ZtElementBuffer EBO;
ZtProgram Program;
ZtTexture Texture0;
ZtTexture Texture1;

glm::mat4 Model = glm::mat4(1.0f);
glm::mat4 View = glm::mat4(1.0f);
glm::mat4 Projection;

void ProcessInput(ZtWindow& Window);

void Rendering(ZtWindow& Window);

ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("Main");

int main()
{
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
        {{ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f}}, // 0
        {{ -0.5f, -0.5f, 0.5f },  { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f}}, // 1
        {{ 0.5f, -0.5f, 0.5f },   { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f}}, // 2
        {{ 0.5f, -0.5f, -0.5f },  { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f}}, // 3

        {{ -0.5f, 0.5f, -0.5f },  { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f}}, // 4
        {{ -0.5f, 0.5f, 0.5f },   { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f}}, // 5
        {{ 0.5f, 0.5f, 0.5f },    { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f}}, // 6
        {{ 0.5f, 0.5f, -0.5f },   { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f}}, // 7
    };

    std::array<unsigned int, 36> Indices {
        0, 1, 2,  //0, 0, 0,
        2, 3, 0,  //0, 0, 0,

        4, 5, 6,  //0, 0, 0,
        6, 7, 4,  //0, 0, 0,

        5, 1, 0,  //0, 0, 0,
        0, 4, 5,  //0, 0, 0,
        
        6, 2, 3,  //0, 0, 0,
        3, 7, 6,  //0, 0, 0,
        
        5, 1, 2,  //0, 0, 0,
        2, 6, 5,  //0, 0, 0,
        
        4, 0, 3,  //0, 0, 0,
        3, 7, 4,  //0, 0, 0,
    };

    Texture0.Generate();
    Texture0.Bind();
    ZtFileFinder::Path TexturePath = RootPath / "Textures" / "checker.png";
    Texture0.LoadFromFile(TexturePath);
    Texture0.GenerateMipmap();

    VBO.Bind();
    VBO.SetData(Vertices, ZtBufferUsage::Static);

    EBO.Bind();
    EBO.SetData(Indices, ZtBufferUsage::Static);

    // Vertices Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ZtVertex), (void*)ZtVertex::GetOffsetToPosition());
    glEnableVertexAttribArray(0);

    // Vertices Colors
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ZtVertex), (void*)ZtVertex::GetOffsetToColor());
    glEnableVertexAttribArray(1);

    // Vertices Texture Coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ZtVertex), (void*)ZtVertex::GetOffsetToTextureCoordinates());
    glEnableVertexAttribArray(2);

    Program.Use();

    VertexShader.Delete();
    FragmentShader.Delete();

    // Lesson about matrices
    glm::mat4 Translate = glm::mat4(1.0f); // Identity Matrix
    Translate = glm::translate(Translate, glm::vec3(0.5f, 0.5f, 0.0f));
    Translate = glm::scale(Translate, glm::vec3(0.8f, 0.8f, 1.0f));
    Translate = glm::rotate(Translate, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    //unsigned int TransformLocation = glGetUniformLocation(Program.GetID(), "Transform");
    //glUniformMatrix4fv(TransformLocation, 1, GL_FALSE, glm::value_ptr(Translate));

    // MVP

    //glm::mat4 Orthographic = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    Model = glm::rotate(Model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f)); // note that we're translating the scene in the reverse direction of where we want to move

    Projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    int ModelLocation = glGetUniformLocation(Program.GetID(), "Model");
    glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));

    int ViewLocation = glGetUniformLocation(Program.GetID(), "View");
    glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(View));

    int ProjectionLocation = glGetUniformLocation(Program.GetID(), "Projection");
    glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, glm::value_ptr(Projection));

    // MVP end

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
    ZtEvent* Event = Window.GetEvent();
    ZtKeyboard* Keyboard = Event->GetKeyboard();
    ZtMouse* Mouse = Event->GetMouse();
    //Logger->info("{0} : {1}", Mouse->GetPositionEvents()[0].Position.x, Mouse->GetPositionEvents()[0].Position.y);

    GLFWwindow* WindowPointer = Window.GetInternalWindow();

    if (Keyboard->IsPressed(ZtKeyboardKey::ESCAPE))
    {
        glfwSetWindowShouldClose(WindowPointer, true);
    }
    else if(Keyboard->IsPressed(ZtKeyboardKey::F1))
    {
        ZtGLContext::FillMode();
    }
    else if (Keyboard->IsPressed(ZtKeyboardKey::F2))
    {
        ZtGLContext::PolygonOnlyMode();
    }
    else if (Keyboard->IsPressed(ZtKeyboardKey::F3))
    {
        ZtGLContext::PointsMode();
    }

    Event->PollEvents();
}

glm::vec3 CubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

void Rendering(ZtWindow& Window)
{
    Window.Clear();

    ZtEvent* Event = Window.GetEvent();
    ZtMouse* Mouse = Event->GetMouse();
    const std::vector<ZtMouseButtonEvent>& MouseEvents = Mouse->GetButtonsEvents();

    thread_local float PreviousTime = 0.f;
    float Time = (float)glfwGetTime();// -PreviousTime;
    PreviousTime = (float)glfwGetTime();

    EBO.Bind();
    for (unsigned int I = 0; I < 10; I++)
    {
        Model = glm::mat4(1.0f);
        Model = glm::translate(Model, CubePositions[I]);
        float Angle = 20.0f * I;
        //Model = glm::rotate(Model, glm::radians(Angle), glm::vec3(1.0f, 0.3f, 0.5f));
        Model = glm::rotate(Model, Time * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        int ModelLocation = Program.GetUniform("Model");
        glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    Window.SwapBuffers();
}