#include "Zinet/GraphicLayer/ZtGLDrawableBase.hpp"
#include "Zinet/GraphicLayer/ZtGLTexture.hpp"

namespace zt::gl
{
	std::vector<RenderStates::Image> DrawableBase::createRenderStatesImages(
		const std::vector<std::reference_wrapper<const Texture>>& textures,
		const std::vector<std::reference_wrapper<const Sampler>>& samplers,
		const std::vector<size_t>& bindings) const
	{
		if (textures.size() != samplers.size() || textures.size() != bindings.size())
		{
			Logger->error("All of the containers must have the same size");
			return {};
		}

		std::vector<RenderStates::Image> result;
		result.reserve(textures.size());

		auto samplerIt = samplers.begin();
		auto bindingIt = bindings.begin();
		for (const Texture& texture : textures)
		{
			result.emplace_back(
				texture.getImageBuffer(),
				*samplerIt,
				texture.getImageView(),
				texture.getImage().getImageLayouts().front(),
				static_cast<std::uint32_t>(*bindingIt)
			);

			++samplerIt;
			++bindingIt;
		}

		return result;
	}

}