#include "Zinet/Reflection/ZtReflectionException.h"

namespace zt {

    ReflectionException::ReflectionException(const std::string& message)
        : MainException(message)
    {
    }

    std::string_view zt::ReflectionException::message() const
    {
        return exceptionMessage;
    }

    char const* zt::ReflectionException::what() const
    {
        return exceptionMessage.c_str();
    }

}