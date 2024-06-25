#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"

#include "Zinet/Core/Reflection/ZtClassesInfos.hpp"

namespace zt::engine
{

	class ZINET_ENGINE_API EngineContext
	{
	public:
		EngineContext() = default;
		EngineContext(const EngineContext& other) = default;
		EngineContext(EngineContext&& other) = default;

		EngineContext& operator = (const EngineContext& other) = default;
		EngineContext& operator = (EngineContext&& other) = default;

		~EngineContext() = default;

	protected:



	};

}