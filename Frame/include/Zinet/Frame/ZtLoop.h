#pragma once

#include "ZtFrameConfig.h"

namespace zt {

	class ZINET_FRAME_API Loop {

	public:

		Loop() noexcept = default;
		Loop(const Loop& other) noexcept = default;
		Loop(Loop&& other) noexcept = default;;

		Loop& operator = (const Loop& other) noexcept = default;
		Loop& operator = (Loop&& other) noexcept = default;

		~Loop() noexcept = default;

		void start();

	protected:

		void begin();

		void loop();

		void update();

		void render();

		void event();
		
		void end();
	};

}