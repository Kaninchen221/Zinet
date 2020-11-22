#include "Zinet/Frame/ZtFrameException.h"

namespace zt {

    FrameException::FrameException(const std::string& message)
        : MainException(message)
    {
    }

    std::string_view zt::FrameException::message() const
    {
        return exceptionMessage;
    }

    char const* zt::FrameException::what() const
    {
        return exceptionMessage.c_str();
    }

}