#pragma once

#include "Zinet/Main/ZtMainException.h"

#include "Zinet/Frame/ZtFrameConfig.h"

namespace zt {
	 
	class ZINET_FRAME_API FrameException : public MainException {

	public:

		FrameException() = default;
		explicit FrameException(const std::string& message);
		FrameException(const FrameException& other) = default;
		FrameException(FrameException&& other) = delete;

		FrameException& operator = (const FrameException& other) = default;
		FrameException& operator = (FrameException&& other) = delete;

		~FrameException() noexcept = default;

	};

}