#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
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
		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Shader");

	public:

		Shader();
		Shader(const Shader& other) = delete;
		Shader(Shader&& other) = default;

		Shader& operator = (const Shader& other) = default;
		Shader& operator = (Shader&& other) = default;

		~Shader() noexcept = default;

		std::string_view getSource() const;

		void loadFromCString(const char* source);

		void loadFromFile(const std::string& path);

		bool parse();
		

	protected:

		std::string source;

	};

}