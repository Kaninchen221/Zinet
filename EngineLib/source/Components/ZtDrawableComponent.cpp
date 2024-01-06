#include "Zinet/Engine/Components/ZtDrawableComponent.hpp"

#include "Zinet/GraphicLayer/ZtGLDrawableBase.hpp"
#include "Zinet/GraphicLayer/ZtGLRendererContext.hpp"
#include "Zinet/GraphicLayer/ZtGLTexture.hpp"

namespace zt::engine
{
	 
	gl::DrawInfo DrawableComponent::createDrawInfo(gl::RendererContext& rendererContext) const
	{
		if (drawable)
		{
			return drawable->createDrawInfo(rendererContext);
		}

		return {};
	}

	gl::RenderStates DrawableComponent::createRenderStates() const
	{
		auto assetsToVectorOfConstReferences = []<class T>(auto assets)
		{
			std::vector<std::reference_wrapper<const T>> references;
			for (const auto& asset : assets)
			{
				if (asset->is<T>())
				{
					const T& texture = asset->get<T>();
					references.push_back(texture);
				}
			}

			return references;
		};

		const std::vector<std::reference_wrapper<const gl::Texture>> textures = assetsToVectorOfConstReferences.operator()<gl::Texture>(texturesAssets);
		const std::vector<std::reference_wrapper<const gl::Sampler>> samplers = assetsToVectorOfConstReferences.operator()<gl::Sampler>(samplersAssets);

		if (drawable)
		{
			gl::RenderStates renderStates =
			{
				.shaders = shaders,
				.descriptors = drawable->createRenderStatesDescriptors(),
				.images = drawable->createRenderStatesImages(textures, samplers, texturesSamplersBindings)
			};

			return renderStates;
		}

		return {};
	}

}