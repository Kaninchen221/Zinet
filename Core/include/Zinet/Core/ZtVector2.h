#pragma once

#include "SFML/System/Vector2.hpp"

template<class T>
using ZtVector2 = sf::Vector2<T>;

typedef ZtVector2<float> ZtVector2F;
typedef ZtVector2<int> ZtVector2I;
typedef ZtVector2<unsigned int> ZtVector2UI;