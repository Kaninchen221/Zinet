#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/Assets/ZtAsset.h"

#include "Zinet/Core/ZtLogger.h"

ZT_REFLECT_NAMESPACE()
namespace zt::engine
{
	ZT_REFLECT_CLASS()
	class ZINET_ENGINE_API TextureAsset : public Asset
	{
		inline static auto Logger = core::ConsoleLogger::Create("TextureAsset");

	public:

		TextureAsset() = default;
		TextureAsset(const TextureAsset& other) = default;
		TextureAsset(TextureAsset&& other) = default;

		TextureAsset& operator = (const TextureAsset& other) = default;
		TextureAsset& operator = (TextureAsset&& other) = default;

		~TextureAsset() noexcept = default;
		
	public:

/*GENERATED_CODE_START*/
TextureAsset() = default;
TextureAsset(const TextureAsset& other) = default;
TextureAsset(TextureAsset&& other) = default;

~TextureAsset() noexcept = default;

TextureAsset& operator = (const TextureAsset& other) = default;
TextureAsset& operator = (TextureAsset&& other) = default;

Asset() = default;
Asset(const Asset& other) = default;
Asset(Asset&& other) = default;

~Asset() noexcept = default;

Asset& operator = (const Asset& other) = default;
Asset& operator = (Asset&& other) = default;

class zt::engine::Asset() = default;
class zt::engine::Asset(const class zt::engine::Asset& other) = default;
class zt::engine::Asset(class zt::engine::Asset&& other) = default;

~class zt::engine::Asset() noexcept = default;

class zt::engine::Asset& operator = (const class zt::engine::Asset& other) = default;
class zt::engine::Asset& operator = (class zt::engine::Asset&& other) = default;

/*GENERATED_CODE_END*/
	};
}