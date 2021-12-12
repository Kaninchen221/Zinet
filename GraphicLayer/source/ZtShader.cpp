#include "Zinet/GraphicLayer/ZtShader.h"

#include <fstream>
#include <sstream>

namespace zt::gl
{

	Shader::~Shader() noexcept
	{
		if (iD != InvalidID)
		{
			deleteResource();
		}
	}

	void Shader::create(ShaderType shaderType)
	{
		type = shaderType;
	}

	void Shader::deleteResource()
	{
		iD = InvalidID;
	}

	ShaderType Shader::getType() const
	{
		return type;
	}

	void Shader::loadFromCString(const char* source)
	{

	}

	void Shader::loadFromFile(const std::string& path)
	{
		std::ifstream file;
		file.open(path);
		if (file.is_open())
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
			std::string string = buffer.str();



			file.close();
		}
		else
		{
			Logger->error("Failed to open shader file with path: {}", path);
		}
	}

	void Shader::compile()
	{

	}

	bool Shader::compileStatus() const
	{
		return {};
	}

	std::string Shader::compileErrorMessage() const
	{
		constexpr size_t bufferSize = 512u;
		char buffer[bufferSize];



		std::string message = buffer;
		return buffer;
	}

}