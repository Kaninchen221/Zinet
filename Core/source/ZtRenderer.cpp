#include "Zinet/Core/ZtRenderer.h"

void ZtRenderer::SetRenderTarget(ZtRenderTarget* RenderTarget)
{
	this->RenderTarget = RenderTarget;
}

ZtRenderTarget* ZtRenderer::GetRenderTarget()
{
	return RenderTarget;
}

void ZtRenderer::Draw(const ZtRenderInfo& RenderInfo)
{
	if (RenderTarget != nullptr)
	{

		RenderTarget->draw(
			RenderInfo.FirstVertexAddress, 
			RenderInfo.VerticesCount,
			RenderInfo.PrimitiveType,
			RenderInfo.RenderStates
		);
	}
}
