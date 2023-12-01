#include "Zinet/Engine/Components/ZtDrawableComponent.h"

#include "Zinet/GraphicLayer/ZtGLDrawableBase.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

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
		if (drawable)
		{
			gl::RenderStates renderStates =
			{
				.shaders = shaders,
				.descriptors = drawable->createRenderStatesDescriptors(),
				.images = drawable->createRenderStatesImages()
			};

			return renderStates;
		}

		return {};
	}

}