#pragma once

#include "gtest/gtest.h"

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"

namespace zt::gl::tests
{

	class BufferTests : public ::testing::Test
	{
	protected:

		struct BufferTest : public Buffer
		{

			vk::BufferCreateInfo createCreateInfo(std::uint64_t size) const override
			{ 
				vk::BufferCreateInfo createInfo;
				createInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
				createInfo.size = size;
				return createInfo;
			}

			VmaAllocationCreateInfo createVmaAllocationCreateInfo(bool randomAccess) const override
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
			int f = 456.342f;
		};

		Renderer renderer;
		std::uint64_t expectedSize = sizeof(MVPFake);
		BufferTest bufferTest;

		void SetUp() override
		{
			renderer.initialize();
			vk::BufferCreateInfo bufferCreateInfo = bufferTest.createCreateInfo(expectedSize);
			VmaAllocationCreateInfo allocationCreateInfo = bufferTest.createVmaAllocationCreateInfo(false);

			bufferTest.create(renderer, bufferCreateInfo, allocationCreateInfo);
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
		VmaAllocationCreateInfo allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(randomAccess);
		ASSERT_EQ(allocationCreateInfo.usage, VMA_MEMORY_USAGE_AUTO);
		ASSERT_TRUE(allocationCreateInfo.flags & VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT);

		randomAccess = true;
		allocationCreateInfo = vertexBuffer.createVmaAllocationCreateInfo(randomAccess);
		ASSERT_TRUE(allocationCreateInfo.flags & VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
	}

	TEST_F(BufferTests, FillWithObject)
	{
		MVPFake object;

		bufferTest.fillWithObject<MVPFake>(object);

		std::pair<void*, std::uint64_t> data = bufferTest.getData();
		
		ASSERT_EQ(data.second, expectedSize);

		int result = std::memcmp(data.first, &object, expectedSize);
		
		ASSERT_EQ(result, 0);

		std::free(data.first);
	}

	TEST_F(BufferTests, FillWithDataContainer)
	{
		std::vector<int> container{ 34, 753345345 };
		bufferTest.fillWithStdContainer<std::vector<int>>(container);

		std::pair<void*, std::uint64_t> data = bufferTest.getData();

		ASSERT_EQ(data.second, expectedSize);

		int result = std::memcmp(data.first, container.data(), expectedSize);

		ASSERT_EQ(result, 0);

		std::free(data.first);
	}

	TEST_F(BufferTests, FillWithCArray)
	{
		int array[2];
		array[0] = 67645;
		array[1] = 123;
		std::size_t size = sizeof(int) * 2u;
		bufferTest.fillWithCArray(array, size);

		std::pair<void*, std::uint64_t> data = bufferTest.getData();
		
		ASSERT_EQ(data.second, size);
		
		int result = std::memcmp(data.first, array, size);
		
		ASSERT_EQ(result, 0);
		
		std::free(data.first);
	}

}