
#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "framework/handlers/entity.h"
#include "framework/util/maths.h"
#include "framework/handlers/settings.h"
#include "custom/others/data.h"

#include "custom/handlers/collisionManager.h"

class player : public entity
{
    public:
        player(unsigned scale, CollisionManager* collisionManager, const sf::Vector2f& position = {300, 300})
            : entity(scale, position, {sf::Vector2f({0, 0}), sf::Vector2f({handle::player::BOUNDS_WIDTH, 0}), 
                sf::Vector2f({handle::player::BOUNDS_WIDTH, handle::player::BOUNDS_HEIGHT}), sf::Vector2f({0, handle::player::BOUNDS_HEIGHT})}, 
                sf::Vector2f(handle::player::BOUNDS_WIDTH / 2, handle::player::BOUNDS_HEIGHT / 2), collisionManager)
        {
            m_body.setTexture(resourceHolder::get().textures.get("entities/player"));
            m_body.setPosition(position);

            m_body.setOrigin(handle::player::BOUNDS_WIDTH / 2, handle::player::BOUNDS_HEIGHT / 2);

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

            c.setFillColor(sf::Color::Blue);
            c.setPosition(m_position);
            renderer.draw(c);
        }

        void update(sf::Time deltaTime)
        {
            m_body.setPosition(m_position);

            sf::Vector2i mouseCoord = sf::Mouse::getPosition();
            this->setRotation(math::angleOf(m_position, sf::Vector2f(mouseCoord)) + 90);
        }

        void fixedUpdate(sf::Time deltaTime)
        {
            
        }

        void handleInput()
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                setPosition({m_position.x, m_position.y - 2});
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                setPosition({m_position.x - 2, m_position.y});
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                setPosition({m_position.x, m_position.y + 2});
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                setPosition({m_position.x + 2, m_position.y});
        }

        void setPosition(const sf::Vector2f& position)
        {
            math::quadPoint pos = quad::toPosition(quad::toAngle(getLocalBounds(), m_angle, quad::getCenter(getLocalBounds())), position);
            if(!isColliding(pos))
            {
                m_position = position;

                this->setBounds(pos);
                m_body.setPosition(position);
            }
        }

        void setRotation(const float angle)
        {
            math::quadPoint pos = quad::toPosition(quad::toAngle(getLocalBounds(), angle, quad::getCenter(getLocalBounds())), m_position);
            if(!isColliding(pos))
            {
                m_angle = angle;

                this->setBounds(pos);
                m_body.setRotation(angle);
            }
        }

        void setScale(unsigned scale)
        {
            m_scale = scale;
        } //work on this

    private:
        sf::Sprite m_body;
};
