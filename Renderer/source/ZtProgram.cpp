#include "Zinet/Renderer/ZtProgram.h"

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

GLuint ZtProgram::GetID() const
{
	return ID;
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
