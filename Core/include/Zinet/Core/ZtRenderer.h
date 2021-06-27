#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtRenderInfo.h"

#include "SFML/Graphics/RenderTarget.hpp"

using ZtRenderTarget = sf::RenderTarget;

class ZtRenderer
{
public:

	void SetRenderTarget(ZtRenderTarget* RenderTarget);

	ZtRenderTarget* GetRenderTarget();

	void Draw(const ZtRenderInfo& RenderInfo);

private:

	ZtRenderTarget* RenderTarget = nullptr;

};