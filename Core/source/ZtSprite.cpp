#include "Zinet/Core/ZtSprite.h"

ZtRenderType ZtSprite::GetRenderType() const
{
    return ZtRenderType::Dynamic;
}

void ZtSprite::SetRenderType(ZtRenderType RenderType)
{
    this->RenderType = RenderType;
}
