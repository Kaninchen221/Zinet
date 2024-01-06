#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"

#include "Zinet/Core/ZtLogger.hpp"

#include <vk_mem_alloc.h>

namespace zt::gl
{
	class Instance;
	class Device;
	class PhysicalDevice;

	class ZINET_GRAPHIC_LAYER_API Vma
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Vma");

	public:

		Vma() = default;
		Vma(const Vma& other) = default;
		Vma(Vma&& other) = default;

		Vma& operator = (const Vma& other) = default;
		Vma& operator = (Vma&& other) = default;

		~Vma() noexcept;

		const VmaAllocator getInternal() const;

		VmaAllocatorCreateInfo createAllocatorCreateInfo(const Instance& instance, const Device& device, const PhysicalDevice& physicalDevice) const;

		void create(const VmaAllocatorCreateInfo& allocatorCreateInfo);

	protected:

		VmaAllocator vmaAllocator{};

	};

}