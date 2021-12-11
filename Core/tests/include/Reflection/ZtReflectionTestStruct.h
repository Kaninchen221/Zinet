#pragma once

namespace zt::tests
{

	struct SimpleTestStruct
	{
		int Integer;

		void Foo() {};
	};

	struct ReflectionTestStruct
	{
		int IntMember = 123124;
		float FloatMember = 234.f;
		unsigned int UnsignedIntMember = 213451u;

		void SimpleMethod();

		int ConstMethodReturnSum(const int& First, const int& Second) const;

		int MethodReturnSum(const int& First, const int& Second);

		void NotLiteralTypeParam(const std::string& String);
	};

	void ReflectionTestStruct::SimpleMethod()
	{}

	inline int ReflectionTestStruct::ConstMethodReturnSum(const int& First, const int& Second) const
	{
		return First + Second;
	}

	inline int ReflectionTestStruct::MethodReturnSum(const int& First, const int& Second)
	{
		return ConstMethodReturnSum(First, Second);
	}

	inline void ReflectionTestStruct::NotLiteralTypeParam(const std::string& String)
	{
	}

}