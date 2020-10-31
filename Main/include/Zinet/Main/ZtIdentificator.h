#pragma once

#include "Zinet/Main/ZtMainConfig.h"

namespace zt {

	class ZINET_MAIN_API Identificator {

	public:

		Identificator() noexcept = delete;
		Identificator(const Identificator& other) noexcept = default;
		Identificator(Identificator&& other) noexcept = default;
		Identificator(size_t identificatorNumber) noexcept;

		Identificator& operator = (const Identificator& other) noexcept = default;
		Identificator& operator = (Identificator&& other) noexcept = default;

		~Identificator() noexcept = default;

		size_t getNumber() const noexcept;

	private:

		size_t number;
	};

}