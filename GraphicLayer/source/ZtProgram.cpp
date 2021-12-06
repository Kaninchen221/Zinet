#include "Zinet/GraphicLayer/ZtProgram.h"

#include "glm/gtc/type_ptr.hpp"

#include "Zinet/GraphicLayer/ZtVertex.h"

ZtProgram::~ZtProgram() noexcept
{
	if (ID != InvalidID)
	{
		Delete();
	}
}

void ZtProgram::Create()
{
	ID = glCreateProgram();
}

void ZtProgram::AttachShader(const ZtShader& Shader) const
{
	glAttachShader(ID, Shader.GetID());
}

void ZtProgram::Link() const
{
	glLinkProgram(ID);
}

bool ZtProgram::LinkStatus() const
{
	int Success{};
	glGetProgramiv(ID, GL_LINK_STATUS, &Success);
	
	return static_cast<bool>(Success);
}

bool ZtProgram::IsValid() const
{
	glValidateProgram(ID);
	GLint IsValid{};
	glGetProgramiv(ID, GL_VALIDATE_STATUS, &IsValid);

	return IsValid;
}

std::string ZtProgram::InfoLog() const
{
	constexpr GLsizei InfoLogSize = 512;
	GLchar InfoLogBuffer[InfoLogSize];

	glGetProgramInfoLog(ID, InfoLogSize, nullptr, InfoLogBuffer);

	return InfoLogBuffer;
}

void ZtProgram::Use() const
{
	glUseProgram(ID);
}

void ZtProgram::Delete()
{
	glDeleteProgram(ID);
	ID = InvalidID;
}

GLint ZtProgram::GetUniform(const std::string& Name)
{
	const GLchar* CStringName = Name.c_str();
	GLint Uniform = glGetUniformLocation(ID, CStringName);
	return Uniform;
}

void ZtProgram::SetUniform1f(const std::string& Name, float Value)
{
	GLint Uniform = GetUniform(Name);
	glUniform1f(Uniform, Value);
}

void ZtProgram::SetUniform2f(const std::string& Name, const glm::vec2& Value)
{
	GLint Uniform = GetUniform(Name);
	glUniform2f(Uniform, Value.x, Value.y);
}

void ZtProgram::SetUniform3f(const std::string& Name, const glm::vec3& Value)
{
	GLint Uniform = GetUniform(Name);
	glUniform3f(Uniform, Value.x, Value.y, Value.z);
}

void ZtProgram::SetUniform4f(const std::string& Name, const glm::vec4& Value)
{
	GLint Uniform = GetUniform(Name);
	glUniform4f(Uniform, Value.x, Value.y, Value.z, Value.w);
}

void ZtProgram::SetUniformMatrix4f(const std::string& Name, const glm::mat4& Value)
{
	GLint Uniform = GetUniform(Name);
	glUniformMatrix4fv(Uniform, 1, GL_FALSE, glm::value_ptr(Value));
}

void ZtProgram::PrepareAttributes() const
{
	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ZtVertex), (void*)ZtVertex::GetOffsetToPosition());
	glEnableVertexAttribArray(0);

	// Colors
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ZtVertex), (void*)ZtVertex::GetOffsetToColor());
	glEnableVertexAttribArray(1);

	// Texture Coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ZtVertex), (void*)ZtVertex::GetOffsetToTextureCoordinates());
	glEnableVertexAttribArray(2);
}
