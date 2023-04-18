#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderTarget.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"

#include <gtest/gtest.h>
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

namespace zt::gl::tests
{

	class RenderTargetSimpleTests : public ::testing::Test
	{
	protected:

		RenderTarget renderTarget;
	};

	TEST_F(RenderTargetSimpleTests, GetImage)
	{
		typedef const Image& (RenderTarget::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RenderTarget::getImage);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const Image& image = renderTarget.getImage();
		ASSERT_EQ(image, nullptr);
	}

	TEST_F(RenderTargetSimpleTests, GetImageView)
	{
		typedef const ImageView& (RenderTarget::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RenderTarget::getImageView);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const ImageView& imageView = renderTarget.getImageView();
		ASSERT_EQ(imageView, nullptr);
	}

	class RenderTargetTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		PhysicalDevice physicalDevice;
		Device device;
		Window window;
		Surface surface;
		Vma vma;

		RenderTarget renderTarget;

		void SetUp() override
		{
			GLFW::Init();

			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			
			physicalDevice.create(instance);

			window.create();

			surface.create(instance, window);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);

			VmaAllocatorCreateInfo vmaCreateInfo = vma.createAllocatorCreateInfo(instance, device, physicalDevice);
			vma.create(vmaCreateInfo);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(RenderTargetTests, Create)
	{
		RenderTarget::CreateInfo renderTargetCreateInfo
		{
			.device = device,
			.vma = vma,
			.width = 400u,
			.height = 400u,
			.format = vk::Format::eR8G8B8A8Srgb
		};

		renderTarget.create(renderTargetCreateInfo);

		const Image& image = renderTarget.getImage();
		ASSERT_NE(image, nullptr);

		const ImageView& imageView = renderTarget.getImageView();
		ASSERT_NE(imageView, nullptr);

		// TODO: Framebuffer etc
	}
}
