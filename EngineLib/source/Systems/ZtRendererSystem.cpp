#include "Zinet/Engine/Systems/ZtRendererSystem.h"

#include "Zinet/GraphicLayer/ZtGLDrawableBase.h"

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

		savedRenderStates.clear();

		renderer.preDraw();
	}

	void RendererSystem::update(core::Time timeElapsed)
	{
		BaseT::update(timeElapsed);

		for (auto& componentStrongRef : componentsStrongRefs)
		{
			if (componentStrongRef.isValid() && componentStrongRef->isDataValid())
			{
				auto& renderStates = savedRenderStates.emplace_back(componentStrongRef->createRenderStates());

				gl::DrawableBase* drawable = componentStrongRef->getDrawable();
				gl::Transform transform = drawable->getTransform();
				Matrix4f modelMatrix = transform.toMatrix();

				auto viewMatrix = camera.viewMatrix();
				auto projectionMatrix = camera.projectionMatrix();
				renderStates.mvp = gl::MVP{ modelMatrix, viewMatrix, projectionMatrix };

				renderer.draw<gl::Vertex>(drawable->createDrawInfo(renderer.getRendererContext()), renderStates);
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