#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtSprite.h"
#include "Zinet/Core/OCS/ZtSystem.h"

#include "SFML/Graphics/RenderTarget.hpp"

class ZINET_CORE_API ZtRenderer : public ZtSystem
{
public:

    void DrawSprite(const ZtSprite& Sprite);

private:

};