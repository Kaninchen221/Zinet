#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

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

		vk::SamplerCreateInfo createCreateInfo(std::uint32_t maxLod = 0.f);

		void create(const Device& device, const vk::SamplerCreateInfo& createInfo);
	};

}