#include "Zinet/Main/ZtMainException.h"

zt::MainException::MainException(const std::string& message)
    : std::exception(message.c_str())
{
    exceptionMessage = message;
}

std::string_view zt::MainException::message() const
{
    return exceptionMessage;
}
