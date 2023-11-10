#include "Zinet/Engine/Systems/ZtRendererSystem.h"

namespace zt::engine
{

	bool RendererSystem::initialize()
	{
		try
		{
			renderer.initialize();
		}
		catch (const std::exception& exception)
		{
			Logger->critical(
				std::format("Failed initialization of renderer system. Exception message: {}", exception.what()));
			return false;
		}

		return true;
	}

	void RendererSystem::preUpdate(core::Time timeElapsed)
	{
		BaseT::preUpdate(timeElapsed);

		renderer.preDraw();
	}

	void RendererSystem::update(core::Time timeElapsed)
	{
		BaseT::update(timeElapsed);

		for (const auto& componentStrongRef : componentsStrongRefs)
		{
			if (componentStrongRef.isValid() && componentStrongRef->isDataValid())
			{
				auto renderStates = componentStrongRef->getRenderStates();
				renderer.draw<gl::Vertex>(componentStrongRef->getDrawInfo(renderer.getRendererContext()), renderStates);
			}
		}
	}

	void RendererSystem::postUpdate(core::Time timeElapsed)
	{
		BaseT::postUpdate(timeElapsed);

		glfwPollEvents();

		renderer.postDraw();
	}

}