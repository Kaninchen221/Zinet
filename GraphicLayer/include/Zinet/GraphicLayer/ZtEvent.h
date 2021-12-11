#pragma once

#include "ZtGraphicLayer.h"
#include "ZtKeyboard.h"
#include "ZtMouse.h"

namespace zt::gl
{

	class Window;

	class ZINET_GRAPHIC_LAYER_API Event
	{

	public:

		void SetWindow(Window* NewWindow);

		const Window* GetWindow() const;

		void PollEvents();

		Keyboard* GetKeyboard();

		Mouse* GetMouse();

		void BindCallbacks();

	protected:

		Window* WindowPointer = nullptr;
		Keyboard Keyboard;
		Mouse Mouse;

	};

}