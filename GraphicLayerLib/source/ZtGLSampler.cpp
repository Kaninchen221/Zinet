#include "Zinet/GraphicLayer/ZtGLSampler.hpp"

#include "Zinet/GraphicLayer/ZtGLDevice.hpp"

namespace zt::gl
{

	vk::SamplerCreateInfo Sampler::createCreateInfo(std::uint32_t maxLod)
	{
		vk::SamplerCreateInfo samplerInfo;
		samplerInfo.magFilter = vk::Filter::eNearest;
		samplerInfo.minFilter = vk::Filter::eNearest;
		samplerInfo.addressModeU = vk::SamplerAddressMode::eClampToBorder;
		samplerInfo.addressModeV = vk::SamplerAddressMode::eClampToBorder;
		samplerInfo.addressModeW = vk::SamplerAddressMode::eClampToBorder;
		samplerInfo.anisotropyEnable = VK_FALSE;
		samplerInfo.borderColor = vk::BorderColor::eIntOpaqueBlack;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;
		samplerInfo.compareEnable = VK_FALSE;
		samplerInfo.compareOp = vk::CompareOp::eAlways;
		samplerInfo.mipmapMode = vk::SamplerMipmapMode::eNearest;
		samplerInfo.mipLodBias = 0.0f;
		samplerInfo.minLod = 0.0f;
		samplerInfo.maxLod = static_cast<float>(maxLod);

		return samplerInfo;
	}

	void Sampler::create(const Device& device, const vk::SamplerCreateInfo& createInfo)
	{
		vk::raii::Sampler tempSampler{ device.getInternal(), createInfo };
		internal.swap(tempSampler);
		tempSampler.release();
	}

}