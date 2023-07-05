#pragma once

#include "Zinet/GraphicLayer/ZtGLTransform.h"

#include "Zinet/Core/ZtTypeTraits.h"

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
		typedef const Vector3f& (Transform::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Transform::getRotation));

		Vector3f expected = { 5.f, 230.f, 1.f };
		transform.setRotation(expected);
		const Vector3f& actual = transform.getRotation();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(TransformTests, SetGetTranslation)
	{
		typedef const Vector3f& (Transform::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Transform::getTranslation));

		Vector3f expected = { 5.f, 230.f, 1.f };
		transform.setTranslation(expected);
		const Vector3f& actual = transform.getTranslation();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(TransformTests, SetGetScale)
	{
		typedef const Vector3f& (Transform::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Transform::getScale));

		Vector3f expected = { 5.f, 230.f, 1.f };
		transform.setScale(expected);
		const Vector3f& actual = transform.getScale();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(TransformTests, DefaultValues)
	{
		const Vector3f& rotation = transform.getRotation();
		Vector3f expectedRotation = { 0.f, 0.f, 0.f };
		ASSERT_EQ(rotation, expectedRotation);

		const Vector3f& translation = transform.getTranslation();
		Vector3f expectedTranslation = { 0.f, 0.f, 0.f };
		ASSERT_EQ(translation, expectedTranslation);

		const Vector3f& scale = transform.getScale();
		Vector3f expectedScale = { 1.f, 1.f, 1.f };
		ASSERT_EQ(scale, expectedScale);
	}

	TEST_F(TransformTests, ToMatrix)
	{
		Matrix4f matrix = transform.toMatrix();
	}

	TEST_F(TransformTests, EqualTest)
	{
		Transform first;
		first.setTranslation({ 12.4f, 3.f, 1.f });
		first.setScale({ 112.4f, 3.42f, 11.f });
		first.setRotation({ 1.41f, 0.412f, 1.212f });

		Transform second;
		second.setTranslation({ 12.4f, 3.f, 1.f });
		second.setScale({ 112.4f, 3.42f, 11.f });
		second.setRotation({ 1.41f, 0.412f, 1.212f });

		ASSERT_EQ(first, second);
	}

	TEST_F(TransformTests, NotEqualTest)
	{
		Transform first;
		first.setTranslation({ 11.4f, 3.f, 1.f });
		first.setScale({ 112.4f, 3.44f, 11.f });
		first.setRotation({ 1.41f, 0.412f, 1.242f });

		Transform second;
		second.setTranslation({ 12.4f, 3.f, 1.f });
		second.setScale({ 112.4f, 3.42f, 11.f });
		second.setRotation({ 1.41f, 0.412f, 1.212f });

		ASSERT_NE(first, second);
	}

	TEST_F(TransformTests, Combine)
	{
		Vector3f rotation = { 1.f, 5.f, 3.f };
		Vector3f translation = { 2.f, 3.f, 4.f };
		Vector3f scale = { 2.4f, 5.2f, 0.25f };

		Transform first;
		first.setTranslation(translation);
		first.setScale(scale);
		first.setRotation(rotation);

		Transform second;
		second.setTranslation(translation);
		second.setScale(scale);
		second.setRotation(rotation);

		first.combine(second);
		ASSERT_EQ(first.getRotation(), rotation + rotation);
		ASSERT_EQ(first.getTranslation(), translation + translation);
		ASSERT_EQ(first.getScale(), scale * scale);
	}

}
