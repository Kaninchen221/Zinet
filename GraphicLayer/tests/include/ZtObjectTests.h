#pragma once

#include "Zinet/GraphicLayer/ZtObject.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtObjectTests : public ::testing::Test
	{
	protected:

		struct ZtDerived : public Object
		{
			ZtDerived() { ID = 5u; }

			void SetID(GLuint NewID) { ID = NewID; }
		};

		Object Object;

	};

	TEST_F(ZtObjectTests, GetIDTest)
	{
		GLuint ActualID = Object.GetID();
		GLuint ExpectedID = Object::InvalidID;

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
		GLuint Actual = Object::InvalidID;
		GLuint Expected = 0u;

		ASSERT_EQ(Actual, Expected);
	}

}