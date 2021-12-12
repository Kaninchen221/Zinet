#include "Zinet/GraphicLayer/ZtProgram.h"

#include "glm/gtc/type_ptr.hpp"

#include "Zinet/GraphicLayer/ZtVertex.h"

namespace zt::gl
{

	Program::~Program() noexcept
	{
		if (iD != InvalidID)
		{
			deleteResource();
		}
	}

	void Program::create()
	{

	}

	void Program::attachShader(const Shader& shader) const
	{

	}

	void Program::link() const
	{

	}

	bool Program::linkStatus() const
	{
		int success{};

		return static_cast<bool>(success);
	}

	bool Program::isValid() const
	{
		GLint isValid{};

		return isValid;
	}

	std::string Program::infoLog() const
	{
		return {};
	}

	void Program::use() const
	{

	}

	void Program::deleteResource()
	{
		iD = InvalidID;
	}

	int Program::getUniform(const std::string& name)
	{
		return 0;
	}

	void Program::setUniform1f(const std::string& name, float value)
	{

	}

	void Program::setUniform2f(const std::string& name, const glm::vec2& value)
	{

	}

	void Program::setUniform3f(const std::string& name, const glm::vec3& value)
	{

	}

	void Program::setUniform4f(const std::string& name, const glm::vec4& value)
	{

	}

	void Program::setUniformMatrix4f(const std::string& name, const glm::mat4& value)
	{

	}

	void Program::prepareAttributes() const
	{

	}

}