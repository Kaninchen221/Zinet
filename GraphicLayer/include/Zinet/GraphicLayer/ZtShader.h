#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtShaderType.h"
#include "Zinet/GraphicLayer/ZtObject.h"

#include "Zinet/Core/ZtLogger.h"

#include <string>

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Shader : public Object
	{
		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Shader");

	public:

		Shader() = default;
		Shader(const Shader& other) = default;
		Shader(Shader&& other) = default;

		Shader& operator = (const Shader& other) = default;
		Shader& operator = (Shader&& other) = default;

		~Shader() noexcept;

		void create(ShaderType shaderType);

		void deleteResource();

		ShaderType getType() const;

		void loadFromCString(const char* source);

		void loadFromFile(const std::string& path);

		void compile();

		bool compileStatus() const;

		std::string compileErrorMessage() const;

	protected:

		ShaderType type{};
	};

}