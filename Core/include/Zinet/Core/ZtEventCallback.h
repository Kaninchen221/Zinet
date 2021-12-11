#pragma once

#include "Zinet/Core/ZtFunctor.h"

#include <memory>

namespace zt
{

	struct EventCallback
	{
		std::weak_ptr<Functor> Functor;
	};

}