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
}

void ZtShader::Delete()
{
	ID = InvalidID;
}

ZtShaderType ZtShader::GetType() const
{
	return Type;
}

void ZtShader::LoadFromCString(const char* Source)
{

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



		File.close();
	}
	else
	{
		Logger->error("Failed to open shader file with path: {}", Path);
	}
}

void ZtShader::Compile()
{

}

bool ZtShader::CompileStatus() const
{
	return {};
}

std::string  ZtShader::CompileErrorMessage() const
{
	constexpr size_t BufferSize = 512u;
	char Buffer[BufferSize];



	std::string Message = Buffer;
	return Buffer;
}
