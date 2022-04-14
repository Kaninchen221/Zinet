#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderPass.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class RenderPassTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<RenderPass> renderPass = std::make_unique<RenderPass>();

	};

	TEST(RenderPass, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<RenderPass, VulkanObject<vk::raii::RenderPass>>);
	}

	TEST_F(RenderPassTests, CreateAttachmentDescriptionTest)
	{
		vk::Format swapChainFormat{};
		vk::AttachmentDescription attachmentDescription = renderPass->createAttachmentDescription(swapChainFormat);

		ASSERT_NE(attachmentDescription, vk::AttachmentDescription{});
	}

	TEST_F(RenderPassTests, CreateAttachmentReferenceTest)
	{
		vk::AttachmentReference attachmentReference = renderPass->createAttachmentReference();

		ASSERT_NE(attachmentReference, vk::AttachmentReference{});
	}

	TEST_F(RenderPassTests, CreateSubpassDescriptionTest)
	{
		vk::SubpassDescription subpassDescription = renderPass->createSubpassDescription();

		ASSERT_NE(subpassDescription, vk::SubpassDescription{});
	}

	TEST_F(RenderPassTests, CreateRenderPassCreateInfoTest)
	{
		vk::RenderPassCreateInfo createInfo = renderPass->createRenderPassCreateInfo();

		ASSERT_NE(createInfo, vk::RenderPassCreateInfo{});
	}

	TEST_F(RenderPassTests, CreateSubpassDependencyTest)
	{
		vk::SubpassDependency subpassDependency = renderPass->createSubpassDependency();

		ASSERT_NE(subpassDependency, vk::SubpassDependency{});
	}

	TEST_F(RenderPassTests, CreateTest)
	{
		GLFW::InitGLFW();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Window window;
		window.create();

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		Device device;
		device.create(physicalDevice, surface);

		renderPass->createAttachmentDescription(vk::Format::eR8G8Unorm);
		renderPass->createAttachmentReference();
		renderPass->createSubpassDescription();
		renderPass->createSubpassDependency();

		renderPass->create(device);
		vk::raii::RenderPass& internal = renderPass->getInternal();

		ASSERT_NE(*internal, *vk::raii::RenderPass{ std::nullptr_t{} });

		renderPass.reset();

		GLFW::DeinitGLFW();
	}
}