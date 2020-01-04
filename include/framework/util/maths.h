
#pragma once

#include <SFML/System/Vector2.hpp>

#include "math.h"

static const float NORMAL_TOLERANCE = 0.0001f;

namespace math
{
    typedef std::array<sf::Vector2f, 4> quadPoint;

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
        return toDegrees(std::atan2((A.y - B.y), (A.x - B.x))) + 180;
    }

    unsigned power(unsigned base, unsigned power)
    {
        return pow(base, power);
    }

    float projectedPoint(sf::Vector2f point, sf::Vector2f slope)
    {
        return (point.x * slope.x) + (point.y * slope.y);
    }

    float rotatedvalueY(float x, float y, float centerX, float centerY, float angle)
    {
        angle = math::toRadians(angle);
        return centerY - (x - centerX)* sin(angle) + (centerY - y) * cos(angle);
    }

    float rotatedvalueX(float x, float y, float centerX, float centerY, float angle)
    {
        angle = math::toRadians(angle);
        return centerX + (x - centerX)* cos(angle) + (centerY - y) * sin(angle);
    }

    sf::Vector2f slope(sf::Vector2f P1, sf::Vector2f P2)
    {
        return sf::Vector2f((P2.x - P1.x) , (P2.y - P1.y));
    }

    quadPoint getPoints(sf::FloatRect rect)
    {
        return {sf::Vector2f({rect.left, rect.top}), sf::Vector2f({rect.left + rect.width, rect.top}), 
                    sf::Vector2f({rect.left + rect.width, rect.top + rect.height}), sf::Vector2f({rect.left, rect.top + rect.height})};
    }

    sf::Vector2f rotatePoint(sf::Vector2f a, float angle, sf::Vector2f p)
    {
        angle = math::toRadians(angle);

        float s = sin(angle);
        float c = cos(angle);

        p.x -= a.x;
        p.y -= a.y;

        float xn = p.x * c - p.y * s;
        float yn = p.x * s + p.y * c;

        p.x = xn + a.x;
        p.y = yn + a.y;
        
        return p;
    }
}

namespace quad
{
    sf::Vector2f getCenter(math::quadPoint obj)
    {
        return (obj[2] - obj[0]) / 2.f + obj[0];
    }

    sf::Vector2f getUpperCenter(math::quadPoint obj)
    {
        return (obj[1] - obj[0]) / 2.f + obj[0];
    }

    math::quadPoint toPosition(math::quadPoint obj, sf::Vector2f position)
    {
        return {sf::Vector2f({position.x + obj[0].x, position.y + obj[0].y}), sf::Vector2f({position.x + obj[1].x, position.y + obj[1].y}), 
            sf::Vector2f({position.x + obj[2].x, position.y + obj[2].y}), sf::Vector2f({position.x + obj[3].x, position.y + obj[3].y})};
    }

    math::quadPoint toAngle(math::quadPoint obj, float angle, sf::Vector2f Ce)
    {
        sf::Vector2f A = math::rotatePoint(Ce, angle, obj[0]);
        sf::Vector2f B = math::rotatePoint(Ce, angle, obj[1]);
        sf::Vector2f C = math::rotatePoint(Ce, angle, obj[2]);
        sf::Vector2f D = math::rotatePoint(Ce, angle, obj[3]);

        return {A, B, C, D};
    }

    math::quadPoint toEverySub(math::quadPoint obj, sf::Vector2f to)
    {
        obj[0] = obj[0] - to;
        obj[1] = obj[1] - to;
        obj[2] = obj[2] - to;
        obj[3] = obj[3] - to;

        return obj;
    }
}
