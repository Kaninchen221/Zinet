#include "Zinet/GraphicLayer/ZtGLShader.h"

#include <fstream>
#include <sstream>

#include "glslang/Public/ShaderLang.h"

namespace zt::gl
{
    Shader::Shader()
    {

    }

	std::string_view Shader::getSource() const
	{
        return source;
	}

	void Shader::loadFromCString(const char* source)
	{
		this->source = source;
	}

	void Shader::loadFromFile(const std::string& path)
	{
		std::ifstream file;
		file.open(path);
		if (file.is_open())
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
            source = buffer.str();

			file.close();
		}
		else
		{
			Logger->error("Failed to open shader file with path: {}", path);
		}
	}

	bool Shader::parse()
	{
        

        return true;
	}

}