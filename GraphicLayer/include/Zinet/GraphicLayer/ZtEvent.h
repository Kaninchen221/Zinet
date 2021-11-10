#pragma once

#include "ZtGraphicLayer.h"
#include "ZtKeyboard.h"
#include "ZtMouse.h"

class ZtWindow;

class ZINET_GRAPHIC_LAYER_API ZtEvent
{

public:

	void SetWindow(ZtWindow* Window);

	const ZtWindow* GetWindow() const;

	void PollEvents();

	ZtKeyboard* GetKeyboard();

	ZtMouse* GetMouse();

	void BindCallbacks();

protected:

	ZtWindow* Window = nullptr;
	ZtKeyboard Keyboard;
	ZtMouse Mouse;

};