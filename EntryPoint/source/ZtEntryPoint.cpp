#include "ZtEntryPoint.h"

void ZtEntryPoint::Start()
{
    Init();
    
    while (!window.shouldBeClosed())
    {
        ProcessInput();
    
        Rendering();
    }
    
    VAO.deleteResource();
    EBO.deleteResource();
    VBO.deleteResource();
    Texture0.deleteResource();
    
    Program.deleteResource();
}

void ZtEntryPoint::Init()
{
    window.createWindow();
    window.initStb();

    GLFWwindow* windowPointer = window.getInternalWindow();

    // Fix problem with not valid vertices positions
    int Width, Height;
    glfwGetFramebufferSize(windowPointer, &Width, &Height);
    window.setViewport(0, 0, Width, Height);
    // End Fix

    window.setClearColor(0.1f, 0.1f, 0.1f, 1.f);

    PrepareShader();

    std::vector<zt::gl::Vertex> Vertices {
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

    zt::FileFinder FileFinder;
    zt::FileFinder::Path RootPath = FileFinder.currentProjectRootPath();

    Texture0.generate();
    Texture0.bind();
    zt::FileFinder::Path TexturePath = RootPath / "Textures" / "checker.png";
    Texture0.loadFromFile(TexturePath);
    Texture0.generateMipmap();

    VAO.generate();
    VBO.generate();
    EBO.generate();

    VAO.bind();

    VBO.bind();
    VBO.setData(Vertices, zt::gl::BufferUsage::Static);

    EBO.bind();
    EBO.setData(Indices, zt::gl::BufferUsage::Static);

    Program.prepareAttributes();

    Program.use();

    VertexShader.deleteResource();
    FragmentShader.deleteResource();

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
    Program.setUniformMatrix4f("Model", Model);

    View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f)); // note that we're translating the scene in the reverse direction of where we want to move
    Program.setUniformMatrix4f("View", View);

    Projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    Program.setUniformMatrix4f("Projection", Projection);

    // MVP end
}

void ZtEntryPoint::ProcessInput()
{
    zt::gl::Event* Event = window.getEvent();
    zt::gl::Keyboard* Keyboard = Event->getKeyboard();
    zt::gl::Mouse* Mouse = Event->getMouse();
    //Logger->info("{0} : {1}", Mouse->GetPositionEvents()[0].Position.x, Mouse->GetPositionEvents()[0].Position.y);

    GLFWwindow* WindowPointer = window.getInternalWindow();

    if (Keyboard->isPressed(zt::gl::KeyboardKey::ESCAPE))
    {
        glfwSetWindowShouldClose(WindowPointer, true);
    }
    else if (Keyboard->isPressed(zt::gl::KeyboardKey::F1))
    {
        zt::gl::Context::FillMode();
    }
    else if (Keyboard->isPressed(zt::gl::KeyboardKey::F2))
    {
        zt::gl::Context::PolygonOnlyMode();
    }
    else if (Keyboard->isPressed(zt::gl::KeyboardKey::F3))
    {
        zt::gl::Context::PointsMode();
    }

    Event->pollEvents();
}

void ZtEntryPoint::Rendering()
{
    window.clear();

    zt::gl::Event* Event = window.getEvent();
    zt::gl::Mouse* Mouse = Event->getMouse();
    const std::vector<zt::gl::MouseButtonEvent>& MouseEvents = Mouse->getButtonsEvents();

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
        int ModelLocation = Program.getUniform("Model");
        //glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));

        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    window.swapBuffers();
}

void ZtEntryPoint::PrepareShader()
{
    zt::FileFinder FileFinder;
    zt::FileFinder::Path RootPath = FileFinder.currentProjectRootPath();

    VertexShader.create(zt::gl::ShaderType::Vertex);
    zt::FileFinder::Path VertexShaderFilePath = RootPath / "Shaders" / "shader.vert";
    VertexShader.loadFromFile(VertexShaderFilePath.string());
    VertexShader.compile();

    bool VertexShaderCompileStatus = VertexShader.compileStatus();
    if (!VertexShaderCompileStatus)
    {
        std::string Message = VertexShader.compileErrorMessage();
        Logger->error("Invalid Vertex Shader {0}", Message);
        return;
    }

    FragmentShader.create(zt::gl::ShaderType::Fragment);
    zt::FileFinder::Path FragmentShaderFilePath = RootPath / "Shaders" / "shader.frag";
    FragmentShader.loadFromFile(FragmentShaderFilePath.string());
    FragmentShader.compile();

    bool FragmentShaderCompileStatus = FragmentShader.compileStatus();
    if (!FragmentShaderCompileStatus)
    {
        std::string Message = FragmentShader.compileErrorMessage();
        Logger->error("Invalid Fragment Shader {0}", Message);
        return;
    }

    Program.create();
    Program.attachShader(VertexShader);
    Program.attachShader(FragmentShader);
    Program.link();

    if (!Program.isValid())
    {
        std::string InfoLog = Program.infoLog();
        Logger->error("Problem with Program {0}", InfoLog);
        return;
    }
}
