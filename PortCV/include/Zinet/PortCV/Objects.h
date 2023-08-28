#pragma once

#include "Zinet/GraphicLayer/ZtGLFlipbook.h"
#include "Zinet/Window/ZtMath.h"
#include "Zinet/GraphicLayer/ZtGLTransform.h"
#include "Zinet/GraphicLayer/ZtGLSprite.h"

#include <filesystem>

#include "imgui.h"

using namespace zt;

class Object
{
public:

	static void ImguiDrawable2DBase(gl::Drawable2DBase& drawable2D, size_t index);

	virtual void create() = 0;
};

class Character : public Object
{

public:

	virtual void create() override;

public:

	gl::Sprite sprite;

};

inline void Character::create()
{
	gl::TextureRegion textureRegion;
	textureRegion.size = Vector2f{ 16.f, 16.f };
	textureRegion.offset = Vector2f{ 16.f, 32.f };
	sprite.setTextureRegion(textureRegion, Vector2f{ 48.f, 80.f });
}

class Campfire : public Object
{

public:

	virtual void create() override;

public:

	gl::Flipbook flipbook;

};

inline void Object::ImguiDrawable2DBase(gl::Drawable2DBase& drawable2D, size_t index)
{
	gl::Transform transform = drawable2D.getTransform();
	Vector3f position = transform.getTranslation();
	Vector3f rotation = transform.getRotation();
	Vector3f scale = transform.getScale();

	std::array<float, 3> rawPosition;
	rawPosition = Math::FromVectorToArray(position);
	std::string positionName = std::string{ "Position " } + std::to_string(static_cast<int>(index));
	ImGui::SliderFloat3(positionName.c_str(), rawPosition.data(), -10.0f, 10.0f);

	std::array<float, 3> rawRotation;
	rawRotation = Math::FromVectorToArray(rotation);
	std::string rotationName = std::string{ "Rotation " } + std::to_string(static_cast<int>(index));
	ImGui::SliderFloat3(rotationName.c_str(), rawRotation.data(), 0.f, 560.0f);

	std::array<float, 3> rawScale;
	rawScale = Math::FromVectorToArray(scale);
	std::string scaleName = std::string{ "Scale " } + std::to_string(static_cast<int>(index));
	ImGui::SliderFloat3(scaleName.c_str(), rawScale.data(), 0.01f, 10.0f);

	ImGui::Spacing();

	position = Math::FromArrayToVector(rawPosition);
	rotation = Math::FromArrayToVector(rawRotation);
	scale = Math::FromArrayToVector(rawScale);
	transform.setTranslation(position);
	transform.setRotation(rotation);
	transform.setScale(scale);
	drawable2D.setTransform(transform);
}

inline void Campfire::create()
{
	gl::TextureRegion textureRegion;
	textureRegion.size = Vector2f{ 16.f, 32.f };
	textureRegion.offset = Vector2f{ 0.f, 0.f };

	std::vector<gl::Flipbook::Frame> frames;
	for (size_t index = 0u; index < 6u; ++index)
	{
		gl::Flipbook::Frame frame;
		frame.time = zt::core::Time::FromSeconds(0.5f);
		frame.shaderTextureRegion = textureRegion.toShaderTextureRegion(Vector2f{ 96.f, 32.f });
		frames.push_back(frame);
		textureRegion.offset.x += 16.f;
	}

	flipbook.setFrames(frames);
}
