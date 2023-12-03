#pragma once

#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/ECS/ZtComponent.h"
#include "Zinet/Engine/Assets/ZtTextureAsset.h"
#include "Zinet/Engine/Assets/ZtAssetReference.h"

namespace zt::gl
{
	class DrawableBase;
	class RendererContext;
}

namespace zt::engine
{
	class ZINET_ENGINE_API DrawableComponent : public ecs::Component
	{
	public:

		DrawableComponent() = default;
		DrawableComponent(core::UniqueID&& uniqueID, core::ID entityID) : Component(std::move(uniqueID), entityID) {}
		DrawableComponent(const DrawableComponent& other)  = default;
		DrawableComponent(DrawableComponent&& other) = default;

		DrawableComponent& operator = (const DrawableComponent& other) = default;
		DrawableComponent& operator = (DrawableComponent&& other) = default;

		~DrawableComponent() noexcept = default;

		gl::DrawInfo createDrawInfo(gl::RendererContext& rendererContext) const;

		gl::RenderStates createRenderStates() const;

		template<std::derived_from<gl::DrawableBase> DrawableType>
		void create();

		const gl::DrawableBase* getDrawable() const { return drawable.get(); };
		gl::DrawableBase* getDrawable() { return drawable.get(); };

		bool isReadyToUse() const override { return drawable.operator bool(); }

		const std::vector<gl::Shader>& getShaders() const { return shaders; };
		void setShaders(const std::vector<gl::Shader>& newShaders) { shaders = newShaders; }

		const std::vector<AssetReference>& getTextures() const { return texturesAssets; }
		void setTextures(const std::vector<AssetReference>& newTexturesAssets) { texturesAssets = newTexturesAssets; }

		const std::vector<AssetReference>& getSamplers() const { return samplersAssets; }
		void setSamplers(const std::vector<AssetReference>& newSamplersAssets) { samplersAssets = newSamplersAssets; }

		const std::vector<size_t>& getTexturesSamplersBindings() const { return texturesSamplersBindings; }
		void setTexturesSamplersBindings(const std::vector<size_t>& newBindigns) { texturesSamplersBindings = newBindigns; }

	protected:

		std::unique_ptr<gl::DrawableBase> drawable;
		std::vector<gl::Shader> shaders;
		std::vector<AssetReference> texturesAssets;
		std::vector<AssetReference> samplersAssets;
		std::vector<size_t> texturesSamplersBindings;

	};

	template<std::derived_from<gl::DrawableBase> DrawableType>
	inline void engine::DrawableComponent::create()
	{
		drawable = std::make_unique<DrawableType>();
	}

}

