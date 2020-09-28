#pragma once

#include "ZtSystemConfig.h"

namespace zt {

	class ZINET_SYSTEM_API SystemInterface {

	public:

		SystemInterface() = default;
		SystemInterface(const SystemInterface& other) = default;
		SystemInterface(SystemInterface&& other) = default;

		SystemInterface& operator = (const SystemInterface& other) = default;
		SystemInterface& operator = (SystemInterface&& other) = default;

		virtual ~SystemInterface() noexcept = default;

		void update();

	};

}