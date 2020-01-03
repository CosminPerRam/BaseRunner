
#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "framework/handlers/entity.h"
#include "framework/util/maths.h"
#include "framework/handlers/settings.h"

#include "custom/handlers/collisionManager.h"

class player : public entity
{
    public:
        player(unsigned scale, CollisionManager* collisionManager, const sf::Vector2f& position = {300, 300})
            : entity(scale, position, {sf::Vector2f({0, 0}), sf::Vector2f({handle::player::BOUNDS_WIDTH, 0}), 
                sf::Vector2f({handle::player::BOUNDS_WIDTH, handle::player::BOUNDS_HEIGHT}), sf::Vector2f({0, handle::player::BOUNDS_HEIGHT})}, collisionManager)
        {
            m_body.setTexture(resourceHolder::get().textures.get("player"));
            m_body.setPosition(position);

            this->setBounds(quad::toPosition(this->getLocalBounds(), position));
        }

        void render(sf::RenderTarget& renderer)
        {
            renderer.draw(m_body);

            sf::CircleShape c;
            c.setRadius(3);
            c.setFillColor(sf::Color::Red);

            math::quadPoint Q = getBounds();

            c.setPosition(Q[0]);
            renderer.draw(c);

            c.setPosition(Q[1]);
            renderer.draw(c);

            c.setPosition(Q[2]);
            renderer.draw(c);

            c.setPosition(Q[3]);
            renderer.draw(c);

            c.setPosition((Q[2] - Q[0]) / 2.f + Q[0]);
            renderer.draw(c);
        }

        void update(sf::Time deltaTime)
        {
            m_body.setPosition(m_position);

            sf::Vector2i mouseCoord = sf::Mouse::getPosition();
            this->setRotation(math::angleOf(m_position, sf::Vector2f(mouseCoord)));
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

            this->setBounds(quad::toPosition(quad::toAngle(getLocalBounds(), m_angle), position));
            m_body.setPosition(position);
        }

        void setRotation(const float angle)
        {
            if(!isColliding(quad::toPosition(quad::toAngle(getLocalBounds(), angle), m_position)))
            {
                m_angle = angle;

                this->setBounds(quad::toPosition(quad::toAngle(getLocalBounds(), angle), m_position));
                m_body.setRotation(angle);
            }
        }

        void setScale(unsigned scale)
        {
            m_scale = scale;
        } //work on this

    private:
        void move(sf::Vector2f to)
        {
            if(!isColliding(quad::toPosition(quad::toAngle(getLocalBounds(), m_angle), to)))
                m_position = to;
        }

        sf::Sprite m_body;
};
