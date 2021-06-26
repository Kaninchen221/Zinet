#pragma once

#include "SFML/Graphics/Rect.hpp"

template<class T>
using ZtRectangle = sf::Rect<T>;

using ZtRectangleF = ZtRectangle<float>;
using ZtRectangleI = ZtRectangle<int>;
using ZtRectangleUI = ZtRectangle<unsigned int>;
