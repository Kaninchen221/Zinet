#include "Zinet/GraphicLayer/ZtGLSampler.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	vk::SamplerCreateInfo Sampler::createCreateInfo()
	{
		vk::SamplerCreateInfo samplerInfo;
		samplerInfo.magFilter = vk::Filter::eLinear;
		samplerInfo.minFilter = vk::Filter::eLinear;
		samplerInfo.addressModeU = vk::SamplerAddressMode::eRepeat;
		samplerInfo.addressModeV = vk::SamplerAddressMode::eRepeat;
		samplerInfo.addressModeW = vk::SamplerAddressMode::eRepeat;
		samplerInfo.anisotropyEnable = VK_FALSE;
		samplerInfo.borderColor = vk::BorderColor::eIntOpaqueBlack;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;
		samplerInfo.compareEnable = VK_FALSE;
		samplerInfo.compareOp = vk::CompareOp::eAlways;
		samplerInfo.mipmapMode = vk::SamplerMipmapMode::eLinear;
		samplerInfo.mipLodBias = 0.0f;
		samplerInfo.minLod = 0.0f;
		samplerInfo.maxLod = 0.0f;

		return samplerInfo;
	}

	void Sampler::create(Device& device, const vk::SamplerCreateInfo& createInfo)
	{
		internal = std::move(vk::raii::Sampler{ device.getInternal(), createInfo });
	}

}