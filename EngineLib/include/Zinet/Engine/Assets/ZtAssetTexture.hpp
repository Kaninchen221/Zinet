#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/Assets/ZtAsset.hpp"

#include "Zinet/Core/ZtLogger.hpp"
#include "Zinet/Core/Reflection/ZtClassInfo.hpp"

#include <tuple>


class Texture {};

ZT_REFLECT_NAMESPACE()
namespace zt::engine
{
	ZT_REFLECT_CLASS()
	class ZINET_ENGINE_API AssetTexture : public Asset
	{
		inline static auto Logger = core::ConsoleLogger::Create("AssetTexture");

	public:
		
	protected:

	public:

/*GENERATED_CODE_START*/
class AssetTextureClassInfo : public zt::core::reflection::ClassInfo
{
public:
    std::string_view getClassName() const override { return "AssetTexture"; }
};

AssetTexture() = default;
AssetTexture(const AssetTexture& other) = default;
AssetTexture(AssetTexture&& other) = default;

~AssetTexture() noexcept = default;

AssetTexture& operator = (const AssetTexture& other) = default;
AssetTexture& operator = (AssetTexture&& other) = default;

auto getCopyOfAllMembers() { return std::make_tuple(); };
/*GENERATED_CODE_END*/
	};
}