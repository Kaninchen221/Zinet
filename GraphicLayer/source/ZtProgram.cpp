#include "Zinet/GraphicLayer/ZtProgram.h"

#include "glm/gtc/type_ptr.hpp"

#include "Zinet/GraphicLayer/ZtVertex.h"

namespace zt::gl
{

	Program::~Program() noexcept
	{
		if (ID != InvalidID)
		{
			Delete();
		}
	}

	void Program::Create()
	{

	}

	void Program::AttachShader(const Shader& Shader) const
	{

	}

	void Program::Link() const
	{

	}

	bool Program::LinkStatus() const
	{
		int Success{};

		return static_cast<bool>(Success);
	}

	bool Program::IsValid() const
	{
		GLint IsValid{};

		return IsValid;
	}

	std::string Program::InfoLog() const
	{
		return {};
	}

	void Program::Use() const
	{

	}

	void Program::Delete()
	{
		ID = InvalidID;
	}

	int Program::GetUniform(const std::string& Name)
	{
		return 0;
	}

	void Program::SetUniform1f(const std::string& Name, float Value)
	{

	}

	void Program::SetUniform2f(const std::string& Name, const glm::vec2& Value)
	{

	}

	void Program::SetUniform3f(const std::string& Name, const glm::vec3& Value)
	{

	}

	void Program::SetUniform4f(const std::string& Name, const glm::vec4& Value)
	{

	}

	void Program::SetUniformMatrix4f(const std::string& Name, const glm::mat4& Value)
	{

	}

	void Program::PrepareAttributes() const
	{

	}

}