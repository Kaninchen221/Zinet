#include "Zinet/Engine/Components/ZtDrawableComponent.h"

#include "Zinet/GraphicLayer/ZtGLDrawableBase.h"

namespace zt::engine
{
	 
	gl::DrawInfo DrawableComponent::getDrawInfo() const
	{
		return {};
	}

	gl::RenderStates DrawableComponent::getRenderStates() const
	{
		return {};
	}

}