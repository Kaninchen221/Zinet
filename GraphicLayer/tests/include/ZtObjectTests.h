#pragma once

#include "Zinet/GraphicLayer/ZtObject.h"

#include "gtest/gtest.h"

class ZtObjectTests : public ::testing::Test
{
protected:

	struct ZtDerived : public ZtObject
	{
		ZtDerived() { ID = 5u; }

		void SetID(GLuint NewID) { ID = NewID; }
	};

	ZtObject Object;

};

TEST_F(ZtObjectTests, GetIDTest)
{
	GLuint ActualID = Object.GetID();
	GLuint ExpectedID = ZtObject::InvalidID;

	ASSERT_EQ(ActualID, ExpectedID);
}

TEST_F(ZtObjectTests, IDTest)
{
	ZtDerived Derived;

	GLuint ExpectedID = 4u;
	Derived.SetID(ExpectedID);
	GLuint ActualID = Derived.GetID();

	ASSERT_EQ(ExpectedID, ActualID);
}

TEST_F(ZtObjectTests, InvalidIDTest)
{
	GLuint Actual = ZtObject::InvalidID;
	GLuint Expected = 0u;

	ASSERT_EQ(Actual, Expected);
}