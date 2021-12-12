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
			ZtDerived() { iD = 5u; }

			void setID(GLuint newID) { iD = newID; }
		};

		Object object;

	};

	TEST_F(ZtObjectTests, GetIDTest)
	{
		GLuint actualID = object.getID();
		GLuint expectedID = Object::InvalidID;

		ASSERT_EQ(actualID, expectedID);
	}

	TEST_F(ZtObjectTests, IDTest)
	{
		ZtDerived derived;

		GLuint expectedID = 4u;
		derived.setID(expectedID);
		GLuint actualID = derived.getID();

		ASSERT_EQ(expectedID, actualID);
	}

	TEST_F(ZtObjectTests, InvalidIDTest)
	{
		GLuint actual = Object::InvalidID;
		GLuint expected = 0u;

		ASSERT_EQ(actual, expected);
	}

}