#pragma once

#include "Zinet/Core/ZtMacroUtilities.h"

struct ZtFunctor
{
	virtual void operator() () {}
};

#define ZINET_FUNCTOR_AFFIX _FUNCTOR_

#define ZINET_MAKE_FUNCTOR(CLASS_NAME, FUNCTION_NAME) ZINET_MAKE_FUNCTOR_PRIVATE(CLASS_NAME, FUNCTION_NAME, ZINET_FUNCTOR_AFFIX)

#define ZINET_MAKE_FUNCTOR_PRIVATE(CLASS_NAME, FUNCTION_NAME, FUNCTOR_AFFIX) \
struct ZINET_CONCAT3(CLASS_NAME, ZINET_FUNCTOR_AFFIX, FUNCTION_NAME) : public ZtFunctor \
{ \
	\
	ZINET_CONCAT3(CLASS_NAME, ZINET_FUNCTOR_AFFIX, FUNCTION_NAME)(CLASS_NAME& Object) : Object(Object) {} \
	\
	void operator() () override \
	{ \
		Object.FUNCTION_NAME(); \
	} \
	\
private: \
	CLASS_NAME& Object; \
}; \


