#pragma once

#include "Zinet/GraphicLayer/ZtGLTransform.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class TransformTests : public ::testing::Test
	{
	protected:

		Transform transform;

	};

	TEST_F(TransformTests, SetGetRotation)
	{
		typedef const Vector4f& (Transform::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&Transform::getRotation));

		Vector4f expected = { 5.f, 230.f, 1.f, 0.232f };
		transform.setRotation(expected);
		const Vector4f& actual = transform.getRotation();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(TransformTests, SetGetTranslation)
	{
		typedef const Vector4f& (Transform::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&Transform::getTranslation));

		Vector4f expected = { 5.f, 230.f, 1.f, 0.232f };
		transform.setTranslation(expected);
		const Vector4f& actual = transform.getTranslation();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(TransformTests, SetGetScale)
	{
		typedef const Vector4f& (Transform::* ExpectedFunction)() const;
		static_assert(IsFunctionEqual<ExpectedFunction>(&Transform::getScale));

		Vector4f expected = { 5.f, 230.f, 1.f, 0.232f };
		transform.setScale(expected);
		const Vector4f& actual = transform.getScale();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(TransformTests, DefaultValues)
	{
		const Vector4f& rotation = transform.getRotation();
		Vector4f expectedRotation = { 0.f, 0.f, 0.f, 1.f };
		ASSERT_EQ(rotation, expectedRotation);

		const Vector4f& translation = transform.getTranslation();
		Vector4f expectedTranslation = { 0.f, 0.f, 0.f, 0.f };
		ASSERT_EQ(translation, expectedTranslation);

		const Vector4f& scale = transform.getScale();
		Vector4f expectedScale = { 1.f, 1.f, 1.f, 0.f };
		ASSERT_EQ(scale, expectedScale);
	}

	TEST_F(TransformTests, ToMatrix)
	{
		Matrix4f matrix = transform.toMatrix();
	}
}
