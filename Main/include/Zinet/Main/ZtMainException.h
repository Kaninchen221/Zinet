#pragma once

#include <exception>
#include <string_view>
#include <string>

#include "Zinet/Main/ZtMainConfig.h"

namespace zt {
	 
	class ZINET_MAIN_API MainException : public std::exception {

	public:

		MainException() = default;
		explicit MainException(const std::string& message);
		MainException(const MainException& other) = default;
		MainException(MainException&& other) = delete;

		MainException& operator = (const MainException& other) = default;
		MainException& operator = (MainException&& other) = delete;

		~MainException() noexcept = default;

		virtual std::string_view message() const;

	private:

		std::string exceptionMessage;

	};

}