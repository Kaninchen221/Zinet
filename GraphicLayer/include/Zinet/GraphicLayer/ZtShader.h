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
		Shader(const Shader& Other) = default;
		Shader(Shader&& Other) = default;

		Shader& operator = (const Shader& Other) = default;
		Shader& operator = (Shader&& Other) = default;

		~Shader() noexcept;

		void Create(ShaderType ShaderType);

		void Delete();

		ShaderType GetType() const;

		void LoadFromCString(const char* Source);

		void LoadFromFile(const std::string& Path);

		void Compile();

		bool CompileStatus() const;

		std::string CompileErrorMessage() const;

	protected:

		ShaderType Type{};
	};

}