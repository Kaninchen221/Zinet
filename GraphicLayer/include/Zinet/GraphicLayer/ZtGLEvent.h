#pragma once

#include "ZtGraphicLayer.h"
#include "ZtGLKeyboard.h"
#include "ZtGLMouse.h"

namespace zt::gl
{
	class Window;

	class ZINET_GRAPHIC_LAYER_API Event
	{

	public:

		void setWindow(Window* newWindow);

		const Window* getWindow() const;

		void pollEvents();

		Keyboard* getKeyboard();

		Mouse* getMouse();

		void bindCallbacks();

	protected:

		Window* window = nullptr;
		Keyboard keyboard;
		Mouse mouse;

	};

}