#pragma once

#include "Zinet/Core/ZtCoreConfig.hpp"

#include "Zinet/Core/Reflection/ZtClassInfo.hpp"

#include <tuple>
#include <memory>

namespace zt::core::reflection
{

	class ZINET_CORE_API ClassesInfos
	{
	public:

		template<class ClassInfoChildClass>
		void addClassInfo();

		std::shared_ptr<ClassInfo> getByClassName(std::string_view className);

	protected:

		std::vector<std::shared_ptr<ClassInfo>> internalClassInfos;

	};

	template<class ClassInfoChildClass>
	void ClassesInfos::addClassInfo()
	{
		internalClassInfos.push_back(std::make_shared<ClassInfoChildClass>());
		internalClassInfos.reserve(internalClassInfos.size() * 2u);
	}

}