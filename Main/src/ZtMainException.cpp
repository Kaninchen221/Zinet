#include "Zinet/Main/ZtMainException.h"

zt::MainException::MainException(const std::string& message)
    : exceptionMessage(message)
{
}

std::string_view zt::MainException::message() const
{
    return exceptionMessage;
}

char const* zt::MainException::what() const
{
    return exceptionMessage.c_str();
}
