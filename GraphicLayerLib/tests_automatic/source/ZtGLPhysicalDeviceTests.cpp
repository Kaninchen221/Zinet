#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"

#include "Zinet/Core/ZtTypeTraits.hpp"

#include "Zinet/Window/ZtWindow.hpp"
#include "Zinet/Window/ZtGLFW.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class PhysicalDeviceSimpleTests : public ::testing::Test
	{
	protected:

		PhysicalDevice physicalDevice;

		static_assert(std::derived_from<PhysicalDevice, VulkanObject<vk::raii::PhysicalDevice>>);
	};

	TEST_F(PhysicalDeviceSimpleTests, GetFeaturesTest)
	{
		[[maybe_unused]] const vk::PhysicalDeviceFeatures& physicalDeviceFeatures = physicalDevice.getFeatures();
	}

	TEST_F(PhysicalDeviceSimpleTests, PhysicalDeviceExtensions)
	{
		const std::vector<const char*>& physicalDeviceExtensions = physicalDevice.getPhysicalDeviceExtensions();

		ASSERT_FALSE(physicalDeviceExtensions.empty());
	}

	class PhysicalDeviceTests : public ::testing::Test
	{
	protected:

		wd::Window window;
		Context context;
		Instance instance;
		Surface surface;
		PhysicalDevice physicalDevice;

		void SetUp() override
		{
			wd::GLFW::Init();

			window.create();

			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);

			surface.create(instance, window);

			bool createResult = physicalDevice.create(instance);

			ASSERT_TRUE(createResult);
		}

		void TearDown() override
		{
			wd::GLFW::Deinit();
		}
	};

	TEST_F(PhysicalDeviceTests, PickQueueFamilyIndexTest)
	{
		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex(surface);
		constexpr uint32_t notExpectedIndex = std::numeric_limits<uint32_t>::max();

		ASSERT_NE(queueFamilyIndex, notExpectedIndex);
	}

	TEST_F(PhysicalDeviceTests, GetSwaptChainSupportDetailsTest)
    {
		SwapChainSupportDetails swapChainSupportDetails = physicalDevice.getSwapChainSupportDetails(surface);

		ASSERT_NE(swapChainSupportDetails.surfaceCapabilities, vk::SurfaceCapabilitiesKHR());
		ASSERT_FALSE(swapChainSupportDetails.surfaceFormats.empty());
		ASSERT_FALSE(swapChainSupportDetails.presentModes.empty());
    }

	TEST_F(PhysicalDeviceTests, AssignValueOperator)
	{
		PhysicalDevice other;
		physicalDevice = other;
	}

	TEST_F(PhysicalDeviceTests, FindSupportedFormat)
	{
		typedef bool (PhysicalDevice::* ExpectedFunction)(const PhysicalDevice::FindSupportedFormatInput&, vk::Format& supportedFormat) const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&PhysicalDevice::findSupportedFormat));

		std::vector<vk::Format> candidates = { /*vk::Format::eD32Sfloat,*/ vk::Format::eD32SfloatS8Uint, vk::Format::eD24UnormS8Uint};
		vk::ImageTiling imageTiling = vk::ImageTiling::eOptimal;
		vk::FormatFeatureFlags formatFeatureFlags = vk::FormatFeatureFlagBits::eDepthStencilAttachment;

		PhysicalDevice::FindSupportedFormatInput input
		{
			.candidates = candidates,
			.imageTiling = imageTiling,
			.formatFeatureFlags = formatFeatureFlags
		};

		vk::Format supportedFormat{};
		bool supportAnyFormat = physicalDevice.findSupportedFormat(input, supportedFormat);

		EXPECT_TRUE(supportAnyFormat);
	}

	TEST_F(PhysicalDeviceTests, IsFormatSupportingGeneratingMipmaps)
	{
		vk::Format format = vk::Format::eR8G8B8A8Srgb;
		bool isSupporitng = physicalDevice.isFormatSupportingGeneratingMipmaps(format);
		ASSERT_TRUE(isSupporitng);
	}
}