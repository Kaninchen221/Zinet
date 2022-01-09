#pragma once

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

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ZtEntryPoint
{
	zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("ZtEntryPoint");

public:

	void Start();

protected:

	void Init();

	void ProcessInput();

	void Rendering();

	void PrepareShader();

	zt::gl::Window window;

	zt::gl::VertexArray VAO;
	zt::gl::VertexBuffer VBO;
	zt::gl::ElementBuffer EBO;
	zt::gl::Shader VertexShader;
	zt::gl::Shader FragmentShader;
	zt::gl::Program Program;
	zt::gl::Texture Texture0;
	zt::gl::Texture Texture1;

	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 View = glm::mat4(1.0f);
	glm::mat4 Projection;

	glm::vec3 CubePositions[10] = {
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
};