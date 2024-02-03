#pragma once

#include "Zinet/Core/ZtCoreConfig.hpp"

#include <typeinfo>

namespace zt::core::reflection
{

	class ZINET_CORE_API ClassPropertyInfo
	{
	public:

		ClassPropertyInfo() = default;
		ClassPropertyInfo(size_t offset, std::string_view name, std::string_view typeName);

		size_t getMemoryOffset() const { return memoryOffset; }
		std::string_view getPropertyName() const { return propertyName; }
		std::string_view getPropertyTypeName() const { return propertyTypeName; }

		template<typename T>
		bool is() const;

		template<typename ReturnT, typename ClassT>
		ReturnT& cast(ClassT* classObjectPtr);

	protected:

		size_t memoryOffset = 0;
		std::string_view propertyName;
		std::string_view propertyTypeName;
	};

	template<typename T>
	bool ClassPropertyInfo::is() const
	{
		const std::type_info& typeInfo = typeid(T);
		const std::string_view typeName = typeInfo.name();
		if (typeName == propertyTypeName)
			return true;
		else
			return false;
	}

	template<typename ReturnT, typename ClassT>
	ReturnT& ClassPropertyInfo::cast(ClassT* classObjectPtr)
	{
		ReturnT* objectPointer = reinterpret_cast<ReturnT*>(classObjectPtr);
		objectPointer += memoryOffset / 4;
		return *objectPointer;
	}
}