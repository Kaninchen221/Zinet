#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Object
	{

	public:

		GLuint const inline static InvalidID = 0u;

		GLuint getID() const;

	protected:

		GLuint iD = InvalidID;

	};

}