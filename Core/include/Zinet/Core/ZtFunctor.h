#pragma once

#include "Zinet/Core/ZtCore.h"

struct ZtFunctor
{
	virtual void operator() () {}
};

#define FUNCTOR_AFFIX _FUNCTOR_

#define MAKE_FUNCTOR(CLASS_NAME, FUNCTION_NAME) MAKE_FUNCTOR_INTERNAL(CLASS_NAME, FUNCTION_NAME, FUNCTOR_AFFIX)

#define MAKE_FUNCTOR_INTERNAL(CLASS_NAME, FUNCTION_NAME, FUNCTOR_AFFIX) \
struct CONCAT3(CLASS_NAME, FUNCTOR_AFFIX, FUNCTION_NAME) : public ZtFunctor \
{ \
	\
	CONCAT3(CLASS_NAME, FUNCTOR_AFFIX, FUNCTION_NAME)(CLASS_NAME& Object) : Object(Object) {} \
	\
	void operator() () override \
	{ \
		Object.FUNCTION_NAME(); \
	} \
	\
private: \
	CLASS_NAME& Object; \
}; \


