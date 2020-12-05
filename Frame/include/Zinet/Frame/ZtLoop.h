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

		~Loop() noexcept = default;

		void start(const zt::LoopSettings& settings, BaseWindow& baseWindow);

	protected:

		void begin();

		void loop(BaseWindow& baseWindow);

		void update();

		void render();

		void event();
		
		void end();

		zt::LoopSettings settings;
	};

}