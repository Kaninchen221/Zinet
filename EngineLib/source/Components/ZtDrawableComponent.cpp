#include "Zinet/Engine/Components/ZtDrawableComponent.h"

#include "Zinet/GraphicLayer/ZtGLDrawableBase.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

namespace zt::engine
{
	 
	gl::DrawInfo DrawableComponent::getDrawInfo(gl::RendererContext& rendererContext) const
	{
		if (drawable)
		{
			return drawable->createDrawInfo(rendererContext);
		}

		return {};
	}

	gl::RenderStates DrawableComponent::getRenderStates() const
	{
		if (drawable)
		{

		}

		return {};
	}

}