#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtKeyboardEvent.h"

#include "Zinet/Core/ZtLogger.h"

#include <vector>

class ZtWindow;

class ZINET_GRAPHIC_LAYER_API ZtKeyboard
{
	friend void ZtKeyCallback(GLFWwindow* InternalWindow, int Key, int ScanCode, int Action, int Mods);

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

	const ZtKeyboardEvent& GetLastEvent() const;

	void SetLastEvent(const ZtKeyboardEvent& Event);

	const ZtKeyboardEvent& GetPreviousEvent() const;

	void SetPreviousEvent(const ZtKeyboardEvent& Event);

	const std::vector<ZtKeyboardEvent>& GetEvents() const;

	ZtBool IsPressed(ZtKeyboardKey Key) const;

	ZtBool IsReleased(ZtKeyboardKey Key) const;

	static void KeyCallback(GLFWwindow* InternalWindow, int Key, int ScanCode, int Action, int Mods);

	void SetMaximumRememberedEvents(ZtSize Value);

	ZtSize GetMaximumRememberedEvents() const;

protected:

	void BindCallbacks();

	ZtWindow* Window = nullptr;

	std::vector<ZtKeyboardEvent> Events;
	size_t MaximumRememberedEvents = 6;

};