#include "Zinet/Engine/Systems/ZtRendererSystem.h"

#include "Zinet/GraphicLayer/ZtGLDrawableBase.h"

#include <algorithm>

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

		createDrawInputs();
	}

	void RendererSystem::update(core::Time timeElapsed)
	{
		BaseT::update(timeElapsed);

		for (auto& componentDrawInput : componentsDrawInputs)
		{
			renderer.draw<gl::Vertex>(std::move(componentDrawInput.drawInfo), componentDrawInput.renderStates);
		}
	}

	void RendererSystem::postUpdate(core::Time timeElapsed)
	{
		BaseT::postUpdate(timeElapsed);

		glfwPollEvents();

		renderer.postDraw();
	}

	void RendererSystem::createDrawInputs()
	{
		componentsDrawInputs.clear();
		for (auto& componentStrongRef : componentsStrongRefs)
		{
			if (componentStrongRef.isValid() && componentStrongRef->isReadyToUse())
			{
				gl::DrawableBase* drawable = componentStrongRef->getDrawable();
				ComponentDrawInfo componentDrawInfo
				{
					.drawInfo = drawable->createDrawInfo(renderer.getRendererContext()),
					.renderStates = componentStrongRef->createRenderStates()
				};

				gl::Transform transform = drawable->getTransform();
				Matrix4f modelMatrix = transform.toMatrix();
				auto viewMatrix = camera.viewMatrix();
				auto projectionMatrix = camera.projectionMatrix();
				componentDrawInfo.renderStates.mvp = gl::MVP{ modelMatrix, viewMatrix, projectionMatrix };

				componentsDrawInputs.emplace_back(std::move(componentDrawInfo));
			}
		}

		auto sortComponentsDrawInfoByTranslationZ = [](const ComponentDrawInfo& first, const ComponentDrawInfo& second)
		{
			return first.renderStates.mvp.model[3].z > second.renderStates.mvp.model[3].z;
		};
		std::ranges::sort(componentsDrawInputs, sortComponentsDrawInfoByTranslationZ);
	}

}