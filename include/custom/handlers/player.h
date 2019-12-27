
#pragma once

#include <SFML/Graphics.hpp>

#include "framework/handlers/entity.h"
#include "framework/util/maths.h"

class player : public entity 
{
    public:
        player(unsigned scale, const sf::Vector2f& position = {0, 0})
            : entity(scale, position)
        {
            rect.setFillColor(sf::Color::Green);
            rect.setSize({scale, scale});

            rect.setPosition(position);
        }

        void render(sf::RenderTarget& renderer)
        {
            renderer.draw(rect);
        }

        void update(sf::Time deltaTime)
        {
            rect.setPosition(m_position);

            sf::Vector2i mouseCoord = sf::Mouse::getPosition();

            rect.setRotation(math::angleOf(m_position, sf::Vector2f(mouseCoord)) + 180);
        }

        void fixedUpdate(sf::Time deltaTime)
        {

        }

        void handleInput()
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                m_position.y -= 2;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                m_position.x -= 2;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                m_position.y += 2;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                m_position.x += 2;
        }

        void setPosition(const sf::Vector2f& position)
        {
            m_position = position;
            rect.setPosition(position);
        }

        void setOrientation(const float& orientation)
        {
            m_orientation = orientation;
            rect.setRotation(orientation);
        }

        void setScale(unsigned scale)
        {
            rect.setSize({scale, scale});
            
            m_scale = scale;
        }

    private:
        sf::RectangleShape rect;
};
