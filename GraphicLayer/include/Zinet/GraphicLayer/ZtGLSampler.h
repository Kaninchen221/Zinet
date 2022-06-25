#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API Sampler : public VulkanObject<vk::raii::Sampler>
	{

	public:

		Sampler() = default;
		Sampler(const Sampler& other) = default;
		Sampler(Sampler&& other) = default;

		Sampler& operator = (const Sampler& other) = default;
		Sampler& operator = (Sampler&& other) = default;

		~Sampler() noexcept = default;

		vk::SamplerCreateInfo createCreateInfo();

		void create(Device& device, const vk::SamplerCreateInfo& createInfo);
	};

}