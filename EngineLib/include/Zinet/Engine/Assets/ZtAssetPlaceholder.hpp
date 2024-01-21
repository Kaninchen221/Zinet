#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/Assets/ZtAsset.hpp"

#include "Zinet/Core/ZtLogger.hpp"

ZT_REFLECT_NAMESPACE()
namespace zt::engine
{
	ZT_REFLECT_CLASS()
	class ZINET_ENGINE_API AssetPlaceholder : public Asset
	{
		inline static auto Logger = core::ConsoleLogger::Create("AssetPlaceholder");

	public:
		
	protected:
	
		ZT_REFLECT_MEMBER(ReadOnly)
		int integer = 0;

		ZT_REFLECT_MEMBER(ReadOnly)
		float f1 = 0;

	public:

/*GENERATED_CODE_START*/
class ClassInfo 
{
public:
    static std::string_view GetClassName() { return "AssetPlaceholder"; }
};

AssetPlaceholder() = default;
AssetPlaceholder(const AssetPlaceholder& other) = default;
AssetPlaceholder(AssetPlaceholder&& other) = default;

~AssetPlaceholder() noexcept = default;

AssetPlaceholder& operator = (const AssetPlaceholder& other) = default;
AssetPlaceholder& operator = (AssetPlaceholder&& other) = default;

const decltype(integer)& getInteger() const { return integer; }

const decltype(f1)& getF1() const { return f1; }

auto getAllMembers() { return std::make_tuple(integer, f1); };
/*GENERATED_CODE_END*/
	};
}