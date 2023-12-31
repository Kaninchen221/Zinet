#pragma once

#include "zinet/lib_name/macros.hpp"

ZT_REFLECT_NAMESPACE()
namespace zt::engine
{
	ZT_REFLECT_CLASS()
	class ZINET_ENGINE_API Asset : public Asset
	{
		ZT_REFLECT_METHOD()
		void update() { /* ... */ }

		ZT_REFLECT_MEMBER()
		int count;

/*GENERATED_CODE_START*/
/*GENERATED_CODE_END*/

	};
}