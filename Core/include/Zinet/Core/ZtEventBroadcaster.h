#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/OCS/ZtObject.h"
#include "Zinet/Core/ZtEventCallback.h"

#include <functional>

#include "plf_colony.h"

class ZtEventBroadcaster
{
public:

	void Add(const ZtEventCallback& EventCallback);

	void Broadcast();

protected:

	plf::colony<ZtEventCallback> Callbacks;

};

inline void ZtEventBroadcaster::Add(const ZtEventCallback& EventCallback)
{
	Callbacks.insert(EventCallback);
}

inline void ZtEventBroadcaster::Broadcast()
{
	for (ZtEventCallback Callback : Callbacks)
	{
		std::shared_ptr<ZtFunctor> FunctorPointer = Callback.Functor.lock();
		if (FunctorPointer)
		{
			FunctorPointer->operator()();
		}
	}
}
