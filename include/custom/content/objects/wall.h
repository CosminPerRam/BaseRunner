
#pragma once

#include "framework/handlers/object.h"

#include <iostream>

class wall : public object
{
    public:
        wall(unsigned scale, unsigned type, CollisionManager* collisionManager, const sf::Vector2u& position)
            : object(scale, sf::Vector2f({position.x * scale, position.y * scale}), 
                {sf::Vector2f({0, 0}), sf::Vector2f({scale, 0}), sf::Vector2f({scale, scale}), sf::Vector2f({0, scale})}, collisionManager), m_type(type)
        {
            if(type == 0)
                rect.setFillColor(sf::Color::Green);
            else if(type == 1)
                rect.setFillColor(sf::Color::Red);
            else 
                rect.setFillColor(sf::Color::Magenta);

            rect.setSize({scale, scale});
            rect.setPosition(m_position);
        }

        void render(sf::RenderTarget& renderer)
        {
            renderer.draw(rect);
        }

        void setPosition(const sf::Vector2u& position)
        {
            
        }

        unsigned getType()
        {
            return m_type;
        }

        void setScale(unsigned scale)
        {
            rect.setSize({scale, scale});
            rect.setPosition({rect.getPosition().x / m_scale * scale, rect.getPosition().y / m_scale * scale});

            m_scale = scale;
        }

    private:
        sf::RectangleShape rect;

        unsigned m_type;
};