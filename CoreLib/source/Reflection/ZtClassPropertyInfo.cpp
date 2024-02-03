#include "Zinet/Core/Reflection/ZtClassPropertyInfo.hpp"

namespace zt::core::reflection
{

	ClassPropertyInfo::ClassPropertyInfo(size_t offset, std::string_view name, std::string_view typeName)
		: memoryOffset{ offset }, propertyName{ name }, propertyTypeName{typeName}
	{

	}

}