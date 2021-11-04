#pragma once

#include "ZtGraphicLayer.h"
#include "ZtKeyboard.h"

class ZtWindow;

class ZINET_GRAPHIC_LAYER_API ZtEvent
{

public:

	void SetWindow(ZtWindow* Window);

	const ZtWindow* GetWindow() const;

	void PollEvents();

	ZtKeyboard* GetKeyboard();

protected:

	ZtWindow* Window = nullptr;
	ZtKeyboard Keyboard;

};