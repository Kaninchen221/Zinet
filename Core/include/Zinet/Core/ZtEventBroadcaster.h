#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/OCS/ZtObject.h"
#include "Zinet/Core/ZtEventCallback.h"

#include <functional>

#include "plf_colony.h"

namespace zt
{

	class EventBroadcaster
	{
	public:

		void Add(const EventCallback& EventCallback);

		void Broadcast();

	protected:

		plf::colony<EventCallback> Callbacks;

	};

	inline void EventBroadcaster::Add(const EventCallback& EventCallback)
	{
		Callbacks.insert(EventCallback);
	}

	inline void EventBroadcaster::Broadcast()
	{
		for (EventCallback Callback : Callbacks)
		{
			std::shared_ptr<Functor> FunctorPointer = Callback.Functor.lock();
			if (FunctorPointer)
			{
				FunctorPointer->operator()();
			}
		}
	}

}
