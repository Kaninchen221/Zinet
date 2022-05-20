#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API DescriptorPool : public VulkanObject<vk::raii::DescriptorPool>
	{

	public:

		DescriptorPool() = default;
		DescriptorPool(const DescriptorPool& other) = default;
		DescriptorPool(DescriptorPool&& other) = default;

		DescriptorPool& operator = (const DescriptorPool& other) = default;
		DescriptorPool& operator = (DescriptorPool&& other) = default;

		~DescriptorPool() noexcept = default;

		const vk::DescriptorPoolSize& createPoolSize();

		const vk::DescriptorPoolSize& getPoolSize() const;

		vk::DescriptorPoolCreateInfo createCreateInfo() const;

		void create(Device& device, const vk::DescriptorPoolCreateInfo& createInfo);

	protected:

		vk::DescriptorPoolSize poolSize{};

	};

}