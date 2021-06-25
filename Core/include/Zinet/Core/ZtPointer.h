#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtObject.h"
#include "Zinet/Core/ZtLogger.h"
#include <type_traits>
#include <memory>

template<class T>
class ZtPointer
{
	static_assert(std::is_base_of_v<ZtObject, T>, "T must inherit from ZtObject");

	inline static ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger(std::string("ZtPointer") + typeid(T).name());

	using ThisType = ZtPointer<T>;

public:

	using Type = T;

	ZtPointer() = default;
	ZtPointer(const ZtPointer& Other);
	ZtPointer(ZtPointer&& Other) = default;
	ThisType& operator = (ThisType& Other);
	ZtPointer& operator = (ZtPointer&& Other) = default;

	~ZtPointer() noexcept = default;

	ZtPointer& operator = (std::unique_ptr<T>& SmartPointer);

	static ZtPointer<T> Create();

	template<class ...Types>
	static ZtPointer<T> Create(const Types&... Arguments);

	bool IsNull() const;

	T* operator -> ();

	operator bool() const;

	template<class DerivedType>
	ZtPointer<DerivedType> CastTo();

protected:
	
	std::unique_ptr<T> ObjectPointer = nullptr;

};

template<class T>
inline ZtPointer<T>::ZtPointer(const ZtPointer& Other)
{
	*this = Other;
}

template<class T>
inline ZtPointer<T>& ZtPointer<T>::operator=(ThisType& Other)
{
	*this = std::move(Other);
	return *this;
}

template<class T>
inline ZtPointer<T>& ZtPointer<T>::operator=(std::unique_ptr<T>& SmartPointer)
{
	ObjectPointer = std::move(SmartPointer);
	return *this;
}

template<class T>
inline ZtPointer<T> ZtPointer<T>::Create()
{
	ZtPointer<T> Pointer;
	Pointer.ObjectPointer = std::make_unique<T>();
	return Pointer;
}

template<class T>
template<class ...Types>
inline ZtPointer<T> ZtPointer<T>::Create(const Types&... Arguments)
{
	ZtPointer<T> Pointer;
	Pointer.ObjectPointer = std::make_unique<T>(Arguments...);
	return Pointer;
}

template<class T>
inline bool ZtPointer<T>::IsNull() const
{
	return ObjectPointer == nullptr;
}

template<class T>
inline T* ZtPointer<T>::operator->()
{
	if (IsNull())
	{
		Logger->critical("Trying to access null pointer");
		ZT_ALWAYS_BREAK;
	}

	return ObjectPointer.get();
}

template<class T>
inline ZtPointer<T>::operator bool() const
{
	bool IsValid = !IsNull();
	return IsValid;
}

template<class T>
template<class DerivedType>
inline ZtPointer<DerivedType> ZtPointer<T>::CastTo()
{
	T* RawPointer = ObjectPointer.release();
	DerivedType* CastedRawPointer = dynamic_cast<DerivedType*>(RawPointer);

	std::unique_ptr<DerivedType> CastedSmartPointer;
	CastedSmartPointer = std::unique_ptr<DerivedType>(CastedRawPointer);

	ZtPointer<DerivedType> ReturnPointer;
	ReturnPointer = CastedSmartPointer;

	return ReturnPointer;
}
