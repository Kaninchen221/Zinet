#pragma once

#include "Zinet/Core/ZtFunctor.h"

#include <memory>

struct ZtEventCallback
{
	std::weak_ptr<ZtFunctor> Functor;
};