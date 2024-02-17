#include "Zinet/Core/Reflection/ZtClassInfos.hpp"

namespace zt::core::reflection
{
	std::shared_ptr<ClassInfo> ClassInfos::getByClassName(std::string_view className)
	{
		for (const auto& classInfo : internalClassInfos)
		{
			if (!classInfo)
				return {};

			if (classInfo->getClassName() == className)
				return classInfo;
		}

		return {};
	}
}