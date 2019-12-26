
#pragma once

#include <SFML/System/Vector2.hpp>

#include "math.h"

namespace math
{
    constexpr float PI = 3.14159265f;
    constexpr float PI_MIN = 3.14f;

    template <typename T>
    T toRadians(T degrees)
    {
        return degrees * PI / 180;
    }

    template <typename T>
    T toDegrees(T radians)
    {
        return (radians * 180) / PI;
    }

    float angleOf(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return toDegrees(std::atan2((A.y - B.y), (A.x - B.x)));
    }

    unsigned power(unsigned base, unsigned power)
    {
        return pow(base, power);
    }
}
