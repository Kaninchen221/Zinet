#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtMousePositionEvent.h"
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

	void SetMaxRememberedButtonsEvents(size_t Size);

	size_t GetMaxRememberedButtonsEvents() const;

	static void ButtonCallback(GLFWwindow* Window, ZtInt Button, ZtInt Action, ZtInt Mods);

	void BindCallbacks();

	static void PositionCallback(GLFWwindow* Window, ZtDouble PositionX, ZtDouble PositionY);

	const std::vector<ZtMousePositionEvent>& GetPositionEvents() const;

	void SetMaxRememberedPositionEvents(size_t Size);

	size_t GetMaxRememberedPositionEvents() const;

protected:

	ZtWindow* InternalWindow = nullptr;
	std::vector<ZtMouseButtonEvent> ButtonsEvents;
	std::vector<ZtMousePositionEvent> PositionEvents;

};