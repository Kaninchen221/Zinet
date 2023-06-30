#pragma once

#include "Zinet/Core/ZtMacroUtilities.h"

namespace zt::core
{

	struct ZINET_CORE_API Functor
	{
		virtual void operator() () {}
	};

	#define ZINET_FUNCTOR_AFFIX _FUNCTOR_
	
	#define ZINET_MAKE_FUNCTOR(CLASS_NAME, FUNCTION_NAME) ZINET_MAKE_FUNCTOR_PRIVATE(CLASS_NAME, FUNCTION_NAME, ZINET_FUNCTOR_AFFIX)
	
	#define ZINET_MAKE_FUNCTOR_PRIVATE(CLASS_NAME, FUNCTION_NAME, FUNCTOR_AFFIX) \
	struct ZINET_CORE_API ZINET_CONCAT3(CLASS_NAME, ZINET_FUNCTOR_AFFIX, FUNCTION_NAME) : public Functor \
	{ \
		\
		ZINET_CONCAT3(CLASS_NAME, ZINET_FUNCTOR_AFFIX, FUNCTION_NAME)(CLASS_NAME& object) : object(object) {} \
		\
		void operator() () override \
		{ \
			object.FUNCTION_NAME(); \
		} \
		\
	private: \
		CLASS_NAME& object; \
	}; \

}