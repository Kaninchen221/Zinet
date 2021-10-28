#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

class ZINET_GRAPHIC_LAYER_API ZtObject
{

public:

	GLuint const inline static InvalidID = 0u;

	GLuint GetID() const;

protected:

	GLuint ID = InvalidID;

};