#pragma once

#include "Zinet/Renderer/ZtRenderer.h"

class ZINET_RENDERER_API ZtObject
{

public:

	GLuint const inline static InvalidID = 0u;

	GLuint GetID() const;

protected:

	GLuint ID = InvalidID;

};