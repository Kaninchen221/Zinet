#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtMouseButtonEvent.h"

#include <vector>

class ZtWindow;

class ZINET_GRAPHIC_LAYER_API ZtMouse
{

public:

	ZtMouse();
	ZtMouse(const ZtMouse& Other) = default;
	ZtMouse(ZtMouse&& Other) = default;

	ZtMouse& operator = (const ZtMouse& Other) = default;
	ZtMouse& operator = (ZtMouse&& Other) = default;

	~ZtMouse() noexcept = default;

	void SetWindow(ZtWindow* Window);

	const ZtWindow* GetWindow() const;

	const std::vector<ZtMouseButtonEvent>& GetButtonsEvents() const;

	void SetMaximumRememberedButtonsEvents(size_t Size);

	size_t GetMaximumRememberedButtonsEvents() const;

	static void ButtonCallback(GLFWwindow* Window, ZtInt Button, ZtInt Action, ZtInt Mods);

	void BindCallbacks();

protected:

	ZtWindow* InternalWindow = nullptr;
	std::vector<ZtMouseButtonEvent> ButtonsEvents;

};