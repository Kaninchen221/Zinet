#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/OCS/ZtObject.h"
#include "Zinet/Core/ZtEventCallback.h"

#include <functional>

#include "plf_colony.h"

namespace zt
{

	class ZINET_CORE_API EventBroadcaster
	{
	public:

		void add(const EventCallback& eventCallback);

		void broadcast();

	protected:

		plf::colony<EventCallback> callbacks;

	};

	inline void EventBroadcaster::add(const EventCallback& eventCallback)
	{
		callbacks.insert(eventCallback);
	}

	inline void EventBroadcaster::broadcast()
	{
		for (EventCallback callback : callbacks)
		{
			std::shared_ptr<Functor> functorPointer = callback.functor.lock();
			if (functorPointer)
			{
				functorPointer->operator()();
			}
		}
	}

}
