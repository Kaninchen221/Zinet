#include "Zinet/GraphicLayer/ZtProgram.h"

#include "glm/gtc/type_ptr.hpp"

#include "Zinet/GraphicLayer/ZtVertex.h"

ZtProgram::~ZtProgram() noexcept
{
	if (ID != InvalidID)
	{
		Delete();
	}
}

void ZtProgram::Create()
{

}

void ZtProgram::AttachShader(const ZtShader& Shader) const
{

}

void ZtProgram::Link() const
{

}

bool ZtProgram::LinkStatus() const
{
	int Success{};

	return static_cast<bool>(Success);
}

bool ZtProgram::IsValid() const
{
	GLint IsValid{};

	return IsValid;
}

std::string ZtProgram::InfoLog() const
{
	return {};
}

void ZtProgram::Use() const
{

}

void ZtProgram::Delete()
{
	ID = InvalidID;
}

int ZtProgram::GetUniform(const std::string& Name)
{
	return 0;
}

void ZtProgram::SetUniform1f(const std::string& Name, float Value)
{

}

void ZtProgram::SetUniform2f(const std::string& Name, const glm::vec2& Value)
{

}

void ZtProgram::SetUniform3f(const std::string& Name, const glm::vec3& Value)
{

}

void ZtProgram::SetUniform4f(const std::string& Name, const glm::vec4& Value)
{

}

void ZtProgram::SetUniformMatrix4f(const std::string& Name, const glm::mat4& Value)
{

}

void ZtProgram::PrepareAttributes() const
{

}
