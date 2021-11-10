#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtKeyboardEvent.h"

#include "Zinet/Core/ZtLogger.h"

#include <vector>

class ZtWindow;

class ZINET_GRAPHIC_LAYER_API ZtKeyboard
{
	static inline ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtKeyboard");

public:

	ZtKeyboard();
	ZtKeyboard(const ZtKeyboard& Other) = default;
	ZtKeyboard(ZtKeyboard&& Other) = default;

	ZtKeyboard& operator = (const ZtKeyboard& Other) = default;
	ZtKeyboard& operator = (ZtKeyboard&& Other) = default;

	~ZtKeyboard() noexcept = default;

	void SetWindow(ZtWindow* Window);

	const ZtWindow* GetWindow() const;

	const std::vector<ZtKeyboardEvent>& GetEvents() const;

	ZtBool IsPressed(ZtKeyboardKey Key) const;

	ZtBool IsReleased(ZtKeyboardKey Key) const;

	void SetMaximumRememberedEvents(ZtSize Value);

	size_t GetMaximumRememberedEvents() const;

	static void KeyCallback(GLFWwindow* InternalWindow, int Key, int ScanCode, int Action, int Mods);

	void BindCallbacks();

protected:

	ZtWindow* Window = nullptr;
	std::vector<ZtKeyboardEvent> Events;

};