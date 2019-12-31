
#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "framework/handlers/entity.h"
#include "framework/util/maths.h"

#include "custom/handlers/collisionManager.h"

class player : public entity 
{
    public:
        player(unsigned scale, CollisionManager* collisionManager, const sf::Vector2f& position = {300, 300})
            : entity(scale, collisionManager, position)
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

            //sf::Vector2i mouseCoord = sf::Mouse::getPosition();
            //rect.setRotation(math::angleOf(m_position, sf::Vector2f(mouseCoord)) + 180);
        }

        void fixedUpdate(sf::Time deltaTime)
        {

        }

        void handleInput()
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                this->move({m_position.x, m_position.y - 2});
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                this->move({m_position.x - 2, m_position.y});
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                this->move({m_position.x, m_position.y + 2});
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                this->move({m_position.x + 2, m_position.y});
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
        void move(const sf::Vector2f& to)
        {
            if(!isColliding(to))
                setPosition(to);
        }

        sf::RectangleShape rect;
};
