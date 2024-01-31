#include "Zinet/Core/ZtCoreConfig.hpp"

namespace zt::core::reflection
{

	class ZINET_CORE_API ClassInfo
	{
	public:

		virtual std::string_view getClassName() const;

	};

}