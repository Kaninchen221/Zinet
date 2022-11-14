#pragma once

#include "ZtGraphicLayer.h"
#include "ZtKeyboard.h"
#include "ZtMouse.h"

namespace zt::gl
{

	class Window;

	// TODO Review that class
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