#pragma once

#include <gtest/gtest.h>

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"

#include "Zinet/Core/ZtTypeTraits.h"

namespace zt::gl::tests
{

	class BufferTests : public ::testing::Test
	{
	protected:

		struct BufferTest : public Buffer
		{

			vk::BufferCreateInfo createCreateInfo(std::uint64_t newSize) const override
			{ 
				vk::BufferCreateInfo createInfo;
				createInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
				createInfo.size = newSize;
				return createInfo;
			}

			VmaAllocationCreateInfo createVmaAllocationCreateInfo([[maybe_unused]] bool randomAccess, [[maybe_unused]] bool useCPUMemory) const override
			{
				VmaAllocationCreateInfo allocationCreateInfo{};
				allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
				allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;

				return allocationCreateInfo;
			}

		};

		struct MVPFake
		{
			int i = 34;
			int f = 456;
		};

		Renderer renderer;
		std::uint64_t expectedSize = sizeof(MVPFake);
		BufferTest bufferTest;

		void SetUp() override
		{
			renderer.initialize();
			vk::BufferCreateInfo vkBufferCreateInfo = bufferTest.createCreateInfo(expectedSize);
			VmaAllocationCreateInfo allocationCreateInfo = bufferTest.createVmaAllocationCreateInfo(false, true);

			RendererContext& rendererContext = renderer.getRendererContext();
			Buffer::CreateInfo bufferCreateInfo{ .device = rendererContext.getDevice(), .vma = rendererContext.getVma() };
			bufferCreateInfo.vkBufferCreateInfo = vkBufferCreateInfo;
			bufferCreateInfo.allocationCreateInfo = allocationCreateInfo;

			bufferTest.create(bufferCreateInfo);
		}
	};

	TEST(Buffer, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Buffer, VulkanObject<vk::raii::Buffer>>);
	}

	TEST(Buffer, IsAbstract)
	{
		static_assert(std::is_abstract<Buffer>::value);
	}

	TEST(Buffer, GetSize)
	{
		StagingBuffer stagingBuffer;
		std::uint64_t actualSize = stagingBuffer.getSize();

		ASSERT_EQ(actualSize, 0u);
	}

	TEST_F(BufferTests, Create)
	{
		ASSERT_NE(*bufferTest.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });

		std::uint64_t actualSize = bufferTest.getSize();
		ASSERT_EQ(actualSize, expectedSize);
	}

	TEST(Buffer, CreateVmaAllocationCreateInfo)
	{
		VertexBuffer vertexBuffer;

		bool randomAccess = false;
		bool useCPUMemory = true;
		VmaAllocationCreateInfo allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(randomAccess, useCPUMemory);
		ASSERT_EQ(allocationCreateInfo.usage, VMA_MEMORY_USAGE_AUTO_PREFER_HOST);
		ASSERT_TRUE(allocationCreateInfo.flags & VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT);

		randomAccess = true;
		useCPUMemory = false;
		allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(randomAccess, useCPUMemory);
		ASSERT_EQ(allocationCreateInfo.usage, VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE);
		ASSERT_TRUE(allocationCreateInfo.flags & VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
	}

	TEST_F(BufferTests, FillWithObject)
	{
		MVPFake object;

		bufferTest.fillWithObject<MVPFake>(object);

		std::unique_ptr<void, decltype(zt::core::LambdaFree)> data = bufferTest.getData();

		int result = std::memcmp(data.get(), &object, expectedSize);
		
		ASSERT_EQ(result, 0);
	}

	TEST_F(BufferTests, FillWithDataContainer)
	{
		std::vector<int> container{ 34, 753345345 };
		bufferTest.fillWithStdContainer<std::vector<int>>(container);

		std::unique_ptr<void, decltype(zt::core::LambdaFree)> data = bufferTest.getData();

		int result = std::memcmp(data.get(), container.data(), expectedSize);

		ASSERT_EQ(result, 0);
	}

	TEST_F(BufferTests, FillWithCArray)
	{
		int array[2];
		array[0] = 67645;
		array[1] = 123;
		bufferTest.fillWithCArray(array);

		std::unique_ptr<void, decltype(zt::core::LambdaFree)> data = bufferTest.getData();
		
		int result = std::memcmp(data.get(), array, bufferTest.getSize());
		
		ASSERT_EQ(result, 0);
	}

}