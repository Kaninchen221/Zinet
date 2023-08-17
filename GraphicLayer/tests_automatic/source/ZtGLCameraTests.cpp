#pragma once

#include "Zinet/GraphicLayer/ZtGLCamera.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class CameraTests : public ::testing::Test
	{
	protected:

		Camera camera;
	};

	TEST_F(CameraTests, DefaultValues)
	{
		Vector3f actualPosition = camera.getPosition();
		Vector3f expectedPosition = { 0.f, 0.f, 5.f };
		EXPECT_EQ(actualPosition, expectedPosition);

		Vector3f actualTarget = camera.getTarget();
		Vector3f expectedTarget = { 0.f, 0.f, 0.f };
		EXPECT_EQ(actualTarget, expectedTarget);

		Vector3f actualCameraOrientation = camera.getCameraOrientation();
		Vector3f expectedCameraOrientation = { 0.f, -1.f, 0.f };
		EXPECT_EQ(actualCameraOrientation, expectedCameraOrientation);

		float actualFov = camera.getFov();
		float expectedFov = 45.f;
		EXPECT_EQ(actualFov, expectedFov);

		float actualAspect = camera.getAspect();
		float expectedAspect = 800.f / 400.f;
		EXPECT_EQ(actualAspect, expectedAspect);

		float actualNear = camera.getNear();
		float expectedNear = 0.01f;
		EXPECT_EQ(actualNear, expectedNear);

		float actualFar = camera.getFar();
		float expectedFar = 10.0f;
		EXPECT_EQ(actualFar, expectedFar);

		Camera::Type actualType = camera.getType();
		Camera::Type expectedType = Camera::Type::Perspective;
		EXPECT_EQ(actualType, expectedType);

		Vector2ui expectedScreenSize = Vector2ui{ 1u, 1u };
		Vector2ui actualScreenSize = camera.getScreenSize();
		EXPECT_EQ(expectedScreenSize, actualScreenSize);
	}

	TEST_F(CameraTests, SetGetPosition)
	{
		typedef const Vector3f& (Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::getPosition));

		Vector3f expected = { 1.3f, 213.f, 0.213f };
		camera.setPosition(expected);
		Vector3f actual = camera.getPosition();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(CameraTests, SetGetTarget)
	{
		typedef const Vector3f& (Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::getTarget));

		Vector3f expected = { 1.3f, 213.f, 0.213f };
		camera.setTarget(expected);
		Vector3f actual = camera.getTarget();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(CameraTests, SetGetCameraOrientation)
	{
		typedef const Vector3f& (Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::getCameraOrientation));

		Vector3f expected = { 1.3f, 213.f, 0.213f };
		camera.setCameraOrientation(expected);
		Vector3f actual = camera.getCameraOrientation();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(CameraTests, ViewMatrix)
	{
		typedef Matrix4f (Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::viewMatrix));

		Matrix4f actual = camera.viewMatrix();
		Matrix4f expected = glm::lookAt(camera.getPosition(), camera.getTarget(), camera.getCameraOrientation());
	}

	TEST_F(CameraTests, SetGetFov)
	{
		typedef float (Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::getFov));
	
		float expected = 90.f;
		camera.setFov(expected);
		float actual = camera.getFov();
	
		ASSERT_EQ(expected, actual);
	}

	TEST_F(CameraTests, SetGetAspect)
	{
		typedef float (Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::getAspect));

		float expected = 400.f / 800.f;
		camera.setAspect(expected);
		float actual = camera.getAspect();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(CameraTests, SetGetNear)
	{
		typedef float (Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::getNear));

		float expected = 0.2f;
		camera.setNear(expected);
		float actual = camera.getNear();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(CameraTests, SetGetFar)
	{
		typedef float (Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::getFar));

		float expected = 20.f;
		camera.setFar(expected);
		float actual = camera.getFar();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(CameraTests, SetGerScreenSize)
	{
		typedef const Vector2ui&(Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::getScreenSize));

		Vector2ui expected = { 24u, 343u };
		camera.setScreenSize(expected);
		Vector2ui actual = camera.getScreenSize();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(CameraTests, OrthographicMatrix)
	{
		typedef Matrix4f(Camera::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Camera::orthographicMatrix));

		Vector2ui screenSize = Vector2ui{ 800, 600 };
		camera.setScreenSize(screenSize);
		Matrix4f actual = camera.orthographicMatrix();
		Matrix4f expected = glm::ortho(screenSize.x / -2.f, screenSize.x / 2.f, screenSize.y / -2.f, screenSize.y / 2.f, camera.getNear(), camera.getFar());

		ASSERT_EQ(actual, expected);
	}

	TEST_F(CameraTests, SetGetType)
	{
		camera.setType(Camera::Type::Ortho);
		Camera::Type type = camera.getType();
		ASSERT_EQ(type, Camera::Type::Ortho);
	}
}
