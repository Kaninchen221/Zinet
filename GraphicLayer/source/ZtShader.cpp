#include "Zinet/GraphicLayer/ZtShader.h"

#include <fstream>
#include <sstream>

namespace zt::gl
{

	Shader::~Shader() noexcept
	{
		if (ID != InvalidID)
		{
			Delete();
		}
	}

	void Shader::Create(ShaderType ShaderType)
	{
		Type = ShaderType;
	}

	void Shader::Delete()
	{
		ID = InvalidID;
	}

	ShaderType Shader::GetType() const
	{
		return Type;
	}

	void Shader::LoadFromCString(const char* Source)
	{

	}

	void Shader::LoadFromFile(const std::string& Path)
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

	void Shader::Compile()
	{

	}

	bool Shader::CompileStatus() const
	{
		return {};
	}

	std::string  Shader::CompileErrorMessage() const
	{
		constexpr size_t BufferSize = 512u;
		char Buffer[BufferSize];



		std::string Message = Buffer;
		return Buffer;
	}

}