#pragma once

struct ZtSimpleTestStruct
{
    int Integer;

    void Foo() {};
};

struct ZtReflectionTestStruct
{
	int IntMember = 123124;
	float FloatMember = 234.f;
	unsigned int UnsignedIntMember = 213451u;

	void SimpleMethod();

	int ConstMethodReturnSum(const int& First, const int& Second) const;

	int MethodReturnSum(const int& First, const int& Second);

	void NotLiteralTypeParam(const std::string& String);
};

void ZtReflectionTestStruct::SimpleMethod()
{}

inline int ZtReflectionTestStruct::ConstMethodReturnSum(const int& First, const int& Second) const
{
	return First + Second;
}

inline int ZtReflectionTestStruct::MethodReturnSum(const int& First, const int& Second)
{
	return ConstMethodReturnSum(First, Second);
}

inline void ZtReflectionTestStruct::NotLiteralTypeParam(const std::string& String)
{
}
