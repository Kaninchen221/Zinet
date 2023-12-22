#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/Assets/ZtAsset.h"

#include "Zinet/Core/ZtLogger.h"

#define ZINET_ENGINE_API
#define ZT_GENERATED_BODY(...)
#define ZT_REFLECT_NAMESPACE(...)
#define ZT_REFLECT_CLASS(...)
#define ZT_REFLECT_METHOD(...)
#define ZT_REFLECT_MEMBER(...)

ZT_REFLECT_NAMESPACE()
namespace zt::engine
{
	// We expect that every reflected class has default, copy, move constructors, destructor and copy, move assign operators
	ZT_REFLECT_CLASS()
	class ZINET_ENGINE_API TextureAsset : public Asset
	{
		inline static auto Logger = core::ConsoleLogger::Create("TextureAsset");

	public:

        // We need handle structs inside class
        ZT_REFLECT_STRUCT()
        struct CreateInputInfo
        {
            int count;
        };

		ZT_GENERATED_BODY()

		/* It will be generated in the ZT_GENERATED_BODY()
		TextureAsset() = default;
		TextureAsset(const TextureAsset& other) = default;
		TextureAsset(TextureAsset&& other) = default;

		TextureAsset& operator = (const TextureAsset& other) = default;
		TextureAsset& operator = (TextureAsset&& other) = default;

		~TextureAsset() noexcept = default;
		*/

		// We don't reflect getters and setters. It will be generated via ZT_REFLECT_MEMBER(...)
		// const Texture& getTexture() const { return texture; }
		// void setTexture(const Texture& newTexture) { texture = newTexture; }

		ZT_REFLECT_METHOD()
		void update() { /* ... */ }

		// I think we can get information about return type automatically
		// There will be problem with "is const", "is virtual" information
		ZT_REFLECT_METHOD()
		bool isValid() const { return true; }

	protected:

		ZT_REFLECT_MEMBER(ReadOnly)
		Texture texture;

	};
}