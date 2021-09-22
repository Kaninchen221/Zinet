#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtRenderType.h"

#include "SFML/Graphics/Sprite.hpp"

class ZINET_CORE_API ZtSprite : public sf::Sprite
{
public:

    void SetRenderType(ZtRenderType RenderType);

    ZtRenderType GetRenderType() const;

protected:

    ZtRenderType RenderType = ZtRenderType::Static;

};