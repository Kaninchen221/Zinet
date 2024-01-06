#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/Assets/ZtAsset.hpp"

#include "Zinet/Core/ZtLogger.hpp"

ZT_REFLECT_NAMESPACE()
namespace zt::engine
{
	ZT_REFLECT_CLASS()
	class ZINET_ENGINE_API TextureAsset : public Asset
	{
		inline static auto Logger = core::ConsoleLogger::Create("TextureAsset");

	public:
		
	protected:
	
		ZT_REFLECT_MEMBER(ReadOnly)
		int count = 0;
		
	public:

/*GENERATED_CODE_START*/
TextureAsset() = default;
TextureAsset(const TextureAsset& other) = default;
TextureAsset(TextureAsset&& other) = default;

~TextureAsset() noexcept = default;

TextureAsset& operator = (const TextureAsset& other) = default;
TextureAsset& operator = (TextureAsset&& other) = default;

const decltype(count)& getCount() const { return count; }

/*GENERATED_CODE_END*/
	};
}