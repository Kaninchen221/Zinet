#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.h"
#include "Zinet/GraphicLayer/ZtGLShaderType.h"

#include "Zinet/Core/ZtLogger.h"

#include <string>

namespace glslang
{
	class TShader;
}

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API Shader
	{
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Shader");

	public:

		Shader() = default;
		Shader(const Shader& other) = delete;
		Shader(Shader&& other) = default;

		Shader& operator = (const Shader& other) = default;
		Shader& operator = (Shader&& other) = default;

		~Shader() noexcept = default;

		std::string_view getSource() const;

		void loadFromCString(const char* newSource);

		bool loadFromFile(const std::string& path);

		ShaderType getType() const;

		void setType(ShaderType shaderType);

		std::string preprocess() const;

		bool compile();
		
		const std::vector<uint32_t>& getCompiled() const;

		void clear();

	protected:

		ShaderType type = ShaderType::Invalid;
		std::string source;
		std::vector<uint32_t> compiled;

	};

}