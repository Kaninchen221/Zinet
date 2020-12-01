#pragma once

#include "Zinet/Main/ZtMainException.h"

#include "Zinet/Reflection/ZtReflectionConfig.h"

namespace zt {
	 
	class ZINET_REFLECTION_API ReflectionException : public MainException {

	public:

		ReflectionException() = default;
		explicit ReflectionException(const std::string& message);
		ReflectionException(const ReflectionException& other) = default;
		ReflectionException(ReflectionException&& other) = delete;

		ReflectionException& operator = (const ReflectionException& other) = default;
		ReflectionException& operator = (ReflectionException&& other) = delete;

		~ReflectionException() noexcept = default;

		virtual std::string_view message() const;

		virtual char const* what() const override;

	private:

		std::string exceptionMessage;

	};

}