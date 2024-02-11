#pragma once

#include "Zinet/Core/ZtCoreConfig.hpp"
#include "Zinet/Core/ZtTypeTraits.hpp"

#include <typeinfo>
#include <optional>
#include <ranges>
#include <xutility>
#include <string>

namespace zt::core::reflection
{
	class ClassPropertyInfo;

	template<size_t Count = 0>
	class ClassPropertiesInfos
	{
	public:

		std::array<ClassPropertyInfo, Count>& get() { return infos; }
		const std::array<ClassPropertyInfo, Count>& get() const { return infos; }

		std::optional<ClassPropertyInfo> findFirstWithPropertyName(const std::string_view propertyName);
		std::optional<ClassPropertyInfo> findFirstWithPropertyName(const std::string_view propertyName) const;

		std::array<ClassPropertyInfo, Count>* operator -> () { return &infos; }
		std::array<ClassPropertyInfo, Count>* operator -> () const { return &infos; }

	protected:
		std::array<ClassPropertyInfo, Count> infos;

	};

	template<size_t Count>
	std::optional<ClassPropertyInfo> ClassPropertiesInfos<Count>::findFirstWithPropertyName(const std::string_view propertyName)
	{
		for (const auto& info : infos)
		{
			if (info.getPropertyName() == propertyName)
			{
				return info;
			}
		}
		return {};
	}

	template<size_t Count>
	std::optional<ClassPropertyInfo> ClassPropertiesInfos<Count>::findFirstWithPropertyName(const std::string_view propertyName) const
	{
		for (const auto& info : infos)
		{
			if (info.getPropertyName() == propertyName)
			{
				return info;
			}
		}
		return {};
	}

	template<size_t Count>
	auto ArrayToClassPropertiesInfos(std::array<ClassPropertyInfo, Count> array)
	{
		ClassPropertiesInfos<Count> classPropertiesInfos;
		for (size_t index = 0u; auto& element : array)
		{
			classPropertiesInfos.get()[index] = element;
			++index;
		}
		return classPropertiesInfos;
	}

	class ZINET_CORE_API ClassPropertyInfo
	{
	public:

		ClassPropertyInfo() = default;
		ClassPropertyInfo(size_t offset, std::string_view name, std::string_view typeName);

		size_t getMemoryOffset() const { return memoryOffset; }
		std::string_view getPropertyName() const { return propertyName; }
		std::string_view getPropertyTypeName() const { return propertyTypeName; }

		template<typename T>
		bool is();

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
	bool ClassPropertyInfo::is()
	{
		const std::type_info& typeInfo = typeid(T);
		const std::string_view typeName = typeInfo.name();
		const std::array<std::string, 2u> prefixes = { "", "::" };
		for (const auto& prefix : prefixes)
		{
			auto const endsWith = prefix + std::string(propertyTypeName);
			if (typeName.ends_with(endsWith))
				return true;
		}
		return false;
	}

	template<typename T>
	bool ClassPropertyInfo::is() const
	{
		const std::type_info& typeInfo = typeid(T);
		const std::string_view typeName = typeInfo.name();
		const std::array<std::string, 2u> prefixes = {"", "::"};
		for (const auto& prefix : prefixes)
		{
			auto const endsWith = prefix + std::string(propertyTypeName);
			if (typeName.ends_with(endsWith))
				return true;
		}
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