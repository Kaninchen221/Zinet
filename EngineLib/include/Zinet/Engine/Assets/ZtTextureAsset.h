#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/Assets/ZtAsset.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::engine
{
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

	protected:



	};
}