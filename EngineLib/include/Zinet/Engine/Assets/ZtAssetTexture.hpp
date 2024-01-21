#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/Assets/ZtAsset.hpp"

#include "Zinet/Core/ZtLogger.hpp"
#include <tuple>

ZT_REFLECT_NAMESPACE()
namespace zt::engine
{
	ZT_REFLECT_CLASS()
	class ZINET_ENGINE_API AssetTexture : public Asset
	{
		inline static auto Logger = core::ConsoleLogger::Create("AssetTexture");

	public:
		
	protected:
	
		ZT_REFLECT_MEMBER(ReadOnly)
		int count = 0;

	public:

/*GENERATED_CODE_START*/
class ClassInfo 
{
public:
    static std::string_view GetClassName() { return "AssetTexture"; }
};

AssetTexture() = default;
AssetTexture(const AssetTexture& other) = default;
AssetTexture(AssetTexture&& other) = default;

~AssetTexture() noexcept = default;

AssetTexture& operator = (const AssetTexture& other) = default;
AssetTexture& operator = (AssetTexture&& other) = default;

const decltype(count)& getCount() const { return count; }

auto getAllMembers() { return std::make_tuple(count); };
/*GENERATED_CODE_END*/
	};
}