#include "Zinet/GraphicLayer/ZtShader.h"

#include <fstream>
#include <sstream>

ZtShader::~ZtShader() noexcept
{
	if (ID != InvalidID)
	{
		Delete();
	}
}

void ZtShader::Create(ZtShaderType ShaderType)
{
	Type = ShaderType;
	ID = glCreateShader(static_cast<GLuint>(ShaderType));
}

void ZtShader::Delete()
{
	glDeleteShader(ID);
	ID = InvalidID;
}

ZtShaderType ZtShader::GetType() const
{
	return Type;
}

void ZtShader::LoadFromCString(const char* Source)
{
	glShaderSource(ID, 1, &Source, NULL);
}

void ZtShader::LoadFromFile(const std::string& Path)
{
	std::ifstream File;
	File.open(Path);
	if (File.is_open())
	{
		std::stringstream Buffer;
		Buffer << File.rdbuf();
		std::string String = Buffer.str();

		const GLchar* Source = String.c_str();
		glShaderSource(ID, 1, &Source, NULL);

		File.close();
	}
	else
	{
		Logger->error("Failed to open shader file with path: {}", Path);
	}
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
