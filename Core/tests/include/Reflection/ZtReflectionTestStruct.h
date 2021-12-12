#pragma once

namespace zt::tests
{

	struct SimpleTestStruct
	{
		int integer;

		void foo() {};
	};

	struct ReflectionTestStruct
	{
		int intMember = 123124;
		float floatMember = 234.f;
		unsigned int unsignedIntMember = 213451u;

		void simpleMethod();

		int constMethodReturnSum(const int& first, const int& second) const;

		int methodReturnSum(const int& first, const int& second);

		void notLiteralTypeParam(const std::string& string);
	};

	void ReflectionTestStruct::simpleMethod()
	{}

	inline int ReflectionTestStruct::constMethodReturnSum(const int& first, const int& second) const
	{
		return first + second;
	}

	inline int ReflectionTestStruct::methodReturnSum(const int& first, const int& second)
	{
		return constMethodReturnSum(first, second);
	}

	inline void ReflectionTestStruct::notLiteralTypeParam(const std::string& string)
	{
	}

}