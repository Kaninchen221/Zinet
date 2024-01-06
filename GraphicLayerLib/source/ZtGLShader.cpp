#include "Zinet/GraphicLayer/ZtGLShader.hpp"

#include "Zinet/Core/ZtFile.hpp"

#include <shaderc/shaderc.hpp>

namespace zt::gl
{

	std::string_view Shader::getSource() const
	{
        return source;
	}

	void Shader::loadFromCString(const char* newSource)
	{
		source = newSource;
	}

	bool Shader::loadFromFile(const std::string& path)
	{
		zt::core::File file;
		file.open(path, zt::core::FileOpenMode::In);
		if (!file.isOpen())
		{
			Logger->error("Can't open file: {}", path);
			return false;
		}

		source = file.readAll();
		return true;
	}

	ShaderType Shader::getType() const
	{
		return type;
	}

	void Shader::setType(ShaderType shaderType)
	{
		type = shaderType;
	}

	std::string Shader::preprocess() const
	{
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		shaderc::PreprocessedSourceCompilationResult result =
			compiler.PreprocessGlsl(source, ShaderTypeToShaderc(type), "shader", options);

		if (result.GetCompilationStatus() != shaderc_compilation_status_success) 
		{
			Logger->error("Failed to preprocess shader, error: {}", result.GetErrorMessage());
			return "";
		}

		return { result.cbegin(), result.cend() };
	}

	bool Shader::compile()
	{
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		shaderc::SpvCompilationResult result =
			compiler.CompileGlslToSpv(source, ShaderTypeToShaderc(type), "shader", options);

		if (result.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			Logger->error("Failed to compile shader, error: {}", result.GetErrorMessage());
			return false;
		}

		compiled = std::vector<uint32_t>{ result.cbegin(), result.cend() };

		return true;
	}

	const std::vector<uint32_t>& Shader::getCompiled() const
	{
		return compiled;
	}

	void Shader::clear()
	{
		compiled.clear();
		source.clear();
	}

}