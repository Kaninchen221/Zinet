#include "Zinet/Frame/ZtFrameException.h"

namespace zt {

    FrameException::FrameException(const std::string& message)
        : MainException(message)
    {
    }

}