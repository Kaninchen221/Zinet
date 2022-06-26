#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	vk::ImageCreateInfo Image::createCreateInfo(std::uint32_t width, std::uint32_t height)
	{
		vk::ImageCreateInfo createInfo{};
		createInfo.imageType = vk::ImageType::e2D;
		createInfo.extent.width = width;
		createInfo.extent.height = height;
		createInfo.extent.depth = 1;
		createInfo.mipLevels = 1;
		createInfo.arrayLayers = 1;
		createInfo.format = vk::Format::eR8G8B8A8Srgb;
		createInfo.tiling = vk::ImageTiling::eOptimal;
		createInfo.initialLayout = vk::ImageLayout::eUndefined;
		createInfo.usage = vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled;
		createInfo.sharingMode = vk::SharingMode::eExclusive;
		createInfo.samples = vk::SampleCountFlagBits::e1;

		return createInfo;
	}

	void Image::create(Device& device, const vk::ImageCreateInfo& createInfo)
	{
		internal = std::move(vk::raii::Image{ device.getInternal(), createInfo });
	}
}