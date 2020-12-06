#pragma once

#include "Zinet/Frame/ZtFrameConfig.h"
#include "Zinet/Frame/ZtFrameException.h"
#include "Zinet/Frame/ZtLoop.h"
#include "Zinet/Frame/ZtWindowSettings.h"

#include "SFML/Graphics/RenderWindow.hpp"

#include <memory>

namespace zt {

	class ZINET_FRAME_API Window {

	public:

		using BaseWindow = typename Loop::BaseWindow;
		using VideoMode = sf::VideoMode;
		using ContextSettings = sf::ContextSettings;
		using LoopPtr = std::unique_ptr<Loop>;

		Window() = delete;
		Window(const Window& other) = delete;
		Window(Window&& other) = delete;

		Window(const WindowSettings& settings);

		Window& operator = (const Window& other) = delete;
		Window& operator = (Window&& other) = delete;

		~Window() noexcept = default;

		void setLoop(LoopPtr& loop) noexcept;

		void startLoop(const LoopSettings& loopSettings);

		static VideoMode CreateVideoMode(const WindowSettings& windowSettings);
		static ContextSettings CreateContextSettings(const WindowSettings& windowSettings);

	private:

		void applySettingsToBaseWindow(const WindowSettings& windowSettings);

		LoopPtr loop;
		BaseWindow baseWindow;

	};

}