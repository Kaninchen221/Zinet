#include "Zinet/Core/OCS/ZtObject.h"

namespace zt
{

    void Object::beginPlay(BeginPlayReason reason)
    {

    }

    void Object::endPlay(EndPlayReason reason)
    {

    }

    void Object::tick(float deltaTime)
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