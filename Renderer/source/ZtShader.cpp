#include "Zinet/Renderer/ZtShader.h"

ZtShader::~ZtShader() noexcept
{
	glDeleteShader(ID);
}

void ZtShader::Create(ZtShaderType ShaderType)
{
	Type = ShaderType;
	ID = glCreateShader(static_cast<GLuint>(ShaderType));
}

ZtShaderType ZtShader::GetType() const
{
	return Type;
}

GLuint ZtShader::GetID() const
{
	return ID;
}

void ZtShader::LoadFromCString(const char* Source)
{
	glShaderSource(ID, 1, &Source, NULL);
}

void ZtShader::Compile()
{
	glCompileShader(ID);
}

bool ZtShader::CompileStatus() const
{
	GLint Success = false;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &Success);
	return Success;
}

std::string  ZtShader::CompileErrorMessage() const
{
	constexpr size_t BufferSize = 512u;
	char Buffer[BufferSize];

	glGetShaderInfoLog(ID, BufferSize, nullptr, Buffer);

	std::string Message = Buffer;
	return Buffer;
}
