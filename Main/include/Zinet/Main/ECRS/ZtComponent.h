#pragma once

#include "Zinet/Main/ZtMainConfig.h"
#include "Zinet/Main/ZtUniqueIndexer.h"
#include "Zinet/Main/ZtIdentificator.h"
#include "Zinet/Main/ZtLogger.h"

#include <memory>
#include <string>

namespace zt {

	class ZINET_MAIN_API Component {

		static inline std::string LoggerName = "ComponentLogger";
		static inline UniqueIndexer ComponentsUniqueIndexer;

	public:

		using Tag = std::string;

		Component() noexcept = delete;
		explicit Component(const Component& other) noexcept;
		explicit Component(Component&& other) noexcept;
		explicit Component(Identificator entityOwnerIdentificator) noexcept;

		Component& operator = (const Component& other) noexcept;
		Component& operator = (Component&& other) noexcept;

		virtual ~Component() noexcept;

		void setOwnerIdentificator(Identificator entityIdentificator) noexcept;
		Identificator getOwnerIdentificator() const noexcept;

		void setTag(const Tag& tag) noexcept;
		Tag getTag() const noexcept;

		Identificator getIdentificator() const noexcept;

	private:

		Identificator uniqueIdentificator;
		Identificator entityOwnerIdentificator;
		Tag tag;

	};
}