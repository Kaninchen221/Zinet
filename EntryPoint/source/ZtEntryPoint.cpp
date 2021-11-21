#include "ZtEntryPoint.h"

void ZtEntryPoint::Start()
{
    Init();

    while (!Window.ShouldBeClosed())
    {
        ProcessInput();

        Rendering();
    }

    VAO.Delete();
    EBO.Delete();
    VBO.Delete();
    Texture0.Delete();

    Program.Delete();
}

void ZtEntryPoint::Init()
{
    Window.CreateWindow();
    Window.InitStb();

    GLFWwindow* WindowPointer = Window.GetInternalWindow();

    // Fix problem with not valid vertices positions
    int Width, Height;
    glfwGetFramebufferSize(WindowPointer, &Width, &Height);
    Window.SetViewport(0, 0, Width, Height);
    // End Fix

    Window.SetClearColor(0.1f, 0.1f, 0.1f, 1.f);

    PrepareShader();

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

    ZtFileFinder FileFinder;
    ZtFileFinder::Path RootPath = FileFinder.CurrentProjectRootPath();

    Texture0.Generate();
    Texture0.Bind();
    ZtFileFinder::Path TexturePath = RootPath / "Textures" / "checker.png";
    Texture0.LoadFromFile(TexturePath);
    Texture0.GenerateMipmap();

    VAO.Generate();
    VBO.Generate();
    EBO.Generate();

    VAO.Bind();

    VBO.Bind();
    VBO.SetData(Vertices, ZtBufferUsage::Static);

    EBO.Bind();
    EBO.SetData(Indices, ZtBufferUsage::Static);

    // Vertices Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ZtVertex), (void*)ZtVertex::GetOffsetToPosition()); // Move this to something like ZtRenderInfo
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
    Program.SetUniformMatrix4f("Model", Model);

    View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f)); // note that we're translating the scene in the reverse direction of where we want to move
    Program.SetUniformMatrix4f("View", View);

    Projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    Program.SetUniformMatrix4f("Projection", Projection);

    // MVP end
}

void ZtEntryPoint::ProcessInput()
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
    else if (Keyboard->IsPressed(ZtKeyboardKey::F1))
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

void ZtEntryPoint::Rendering()
{
    Window.Clear();

    ZtEvent* Event = Window.GetEvent();
    ZtMouse* Mouse = Event->GetMouse();
    const std::vector<ZtMouseButtonEvent>& MouseEvents = Mouse->GetButtonsEvents();

    thread_local float PreviousTime = 0.f;
    float Time = (float)glfwGetTime();// -PreviousTime;
    PreviousTime = (float)glfwGetTime();

    //EBO.Bind();
    for (unsigned int I = 0; I < 10; I++)
    {
        Model = glm::mat4(1.0f);
        Model = glm::translate(Model, CubePositions[I]);
        float Angle = 20.0f * I;
        Model = glm::rotate(Model, Time * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        int ModelLocation = Program.GetUniform("Model");
        glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    Window.SwapBuffers();
}

void ZtEntryPoint::PrepareShader()
{
    ZtFileFinder FileFinder;
    ZtFileFinder::Path RootPath = FileFinder.CurrentProjectRootPath();

    VertexShader.Create(ZtShaderType::Vertex);
    ZtFileFinder::Path VertexShaderFilePath = RootPath / "Shaders" / "shader.vert";
    VertexShader.LoadFromFile(VertexShaderFilePath.string());
    VertexShader.Compile();

    bool VertexShaderCompileStatus = VertexShader.CompileStatus();
    if (!VertexShaderCompileStatus)
    {
        std::string Message = VertexShader.CompileErrorMessage();
        Logger->error("Invalid Vertex Shader {0}", Message);
        return;
    }

    FragmentShader.Create(ZtShaderType::Fragment);
    ZtFileFinder::Path FragmentShaderFilePath = RootPath / "Shaders" / "shader.frag";
    FragmentShader.LoadFromFile(FragmentShaderFilePath.string());
    FragmentShader.Compile();

    bool FragmentShaderCompileStatus = FragmentShader.CompileStatus();
    if (!FragmentShaderCompileStatus)
    {
        std::string Message = FragmentShader.CompileErrorMessage();
        Logger->error("Invalid Fragment Shader {0}", Message);
        return;
    }

    Program.Create();
    Program.AttachShader(VertexShader);
    Program.AttachShader(FragmentShader);
    Program.Link();

    if (!Program.IsValid())
    {
        std::string InfoLog = Program.InfoLog();
        Logger->error("Problem with Program {0}", InfoLog);
        return;
    }
}
