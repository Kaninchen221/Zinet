#include "Zinet/GraphicLayer/ZtProgram.h"

#include <gtc/type_ptr.hpp>

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

void ZtProgram::SetUniform1f(GLint Uniform, float Value)
{
	glUniform1f(Uniform, Value);
}

void ZtProgram::SetUniform2f(GLint Uniform, const glm::vec2& Value)
{
	glUniform2f(Uniform, Value.x, Value.y);
}

void ZtProgram::SetUniform3f(GLint Uniform, const glm::vec3& Value)
{
	glUniform3f(Uniform, Value.x, Value.y, Value.z);
}

void ZtProgram::SetUniform4f(GLint Uniform, const glm::vec4& Value)
{
	glUniform4f(Uniform, Value.x, Value.y, Value.z, Value.w);
}
