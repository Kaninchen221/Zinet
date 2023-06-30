#include "Zinet/Core/OCS/ZtObject.h"

namespace zt::core
{

    void Object::beginPlay([[maybe_unused]] BeginPlayReason reason)
    {

    }

    void Object::endPlay([[maybe_unused]] EndPlayReason reason)
    {

    }

    void Object::tick([[maybe_unused]] float deltaTime)
    {

    }

    bool Object::getShouldTick() const
    {
        return shouldTick;
    }

    void Object::setShouldTick(bool value)
    {
        shouldTick = value;
    }

}