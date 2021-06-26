#pragma once

#include "SFML/System/Vector3.hpp"

template<class T>
using ZtVector3 = sf::Vector2<T>;

typedef ZtVector3<float> ZtVector3F;
typedef ZtVector3<int> ZtVector3I;
typedef ZtVector3<unsigned int> ZtVector3UI;