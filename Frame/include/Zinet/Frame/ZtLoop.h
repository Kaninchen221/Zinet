#pragma once

#include "ZtFrameConfig.h"
#include "ZtLoopSettings.h"

#include "SFML/Graphics/RenderWindow.hpp"

namespace zt {

	class ZINET_FRAME_API Loop {

	public:

		using BaseWindow = sf::RenderWindow;

		Loop() noexcept = default;
		Loop(const Loop& other) noexcept = default;
		Loop(Loop&& other) noexcept = default;

		Loop& operator = (const Loop& other) noexcept = default;
		Loop& operator = (Loop&& other) noexcept = default;

		virtual ~Loop() noexcept = default;

		virtual void start(const LoopSettings& settings, BaseWindow& baseWindow) final;

	protected:

		virtual void begin() = 0;
		virtual void loop(BaseWindow& baseWindow) = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void event() = 0;
		virtual void end() = 0;

		LoopSettings settings;

	};

}