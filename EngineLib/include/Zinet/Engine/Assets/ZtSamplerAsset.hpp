#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/Assets/ZtAsset.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::engine
{
	class ZINET_ENGINE_API SamplerAsset : public Asset
	{
		inline static auto Logger = core::ConsoleLogger::Create("SamplerAsset");

	public:

		SamplerAsset() = default;
		SamplerAsset(const SamplerAsset& other) = default;
		SamplerAsset(SamplerAsset&& other) = default;

		SamplerAsset& operator = (const SamplerAsset& other) = default;
		SamplerAsset& operator = (SamplerAsset&& other) = default;

		~SamplerAsset() noexcept = default;

	protected:



	};
}