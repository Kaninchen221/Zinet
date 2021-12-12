#pragma once

#include "Zinet/Core/ZtFunctor.h"

#include <memory>

namespace zt
{

	struct ZINET_CORE_API EventCallback
	{
		std::weak_ptr<Functor> functor;
	};

}