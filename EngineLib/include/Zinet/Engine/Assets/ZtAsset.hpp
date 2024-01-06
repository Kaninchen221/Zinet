#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"

#include "Zinet/Core/ZtLogger.hpp"

#include <any>

namespace zt::engine
{
	class ZINET_ENGINE_API Asset
	{
		inline static auto Logger = core::ConsoleLogger::Create("Asset");

	public:

		Asset() = default;
		Asset(const Asset& other) = default;
		Asset(Asset&& other) = default;

		Asset& operator = (const Asset& other) = default;
		Asset& operator = (Asset&& other) = default;

		~Asset() noexcept = default;

		const std::any& getAny() const { return any; }
		std::any& getAny() { return any; }

		template<class T>
		void create() { any = std::make_any<T>(); }

		template<class T>
		T& get();

		template<class T>
		const T& get() const;

		bool isValid() const { return any.has_value(); }

		template<class T>
		bool is() const;

		void destroy() { any.reset(); }

	protected:

		std::any any;

	};

	template<class T>
	T& Asset::get()
	{
		T* rawPointer = std::any_cast<T>(&any);
		if (!rawPointer)
			throw std::bad_cast{};

		return *rawPointer;
	}

	template<class T>
	const T& Asset::get() const
	{
		const T* rawPointer = std::any_cast<T>(&any);
		if (!rawPointer)
			throw std::bad_cast{};

		return *rawPointer;
	}

	template<class T>
	bool Asset::is() const
	{
		const T* rawPointer = std::any_cast<T>(&any);
		if (rawPointer)
			return true;
		else
			return false;
	}

}