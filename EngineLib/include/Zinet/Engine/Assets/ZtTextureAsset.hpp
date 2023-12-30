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

class zt::engine::ZINET_API_IMPORT() = default;
class zt::engine::ZINET_API_IMPORT(const class zt::engine::ZINET_API_IMPORT& other) = default;
class zt::engine::ZINET_API_IMPORT(class zt::engine::ZINET_API_IMPORT&& other) = default;

~class zt::engine::ZINET_API_IMPORT() noexcept = default;

class zt::engine::ZINET_API_IMPORT& operator = (const class zt::engine::ZINET_API_IMPORT& other) = default;
class zt::engine::ZINET_API_IMPORT& operator = (class zt::engine::ZINET_API_IMPORT&& other) = default;

class ClassInfo 
{
public:
    static std::string_view GetClassName() const { return "class zt::engine::ZINET_API_IMPORT"; }
};
/*GENERATED_CODE_END*/
	};
}