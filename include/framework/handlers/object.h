
#pragma once

#include <SFML/Graphics.hpp>

static unsigned oid = 0;

class object
{
    public:
        object(unsigned scale, const sf::Vector2f& position)
            : m_scale(scale), m_position(position)
        {
            m_oid = oid++;
        }

        virtual void update(sf::Time deltaTime) {}
        virtual void fixedUpdate(sf::Time deltaTime) {}
        virtual void render(sf::RenderTarget& renderer) = 0;

        virtual void setPosition(const sf::Vector2f& position) {}
        virtual void setOrientation(const float& orientation) {}

        sf::Vector2f getPosition() {
            return m_position;
        }

        unsigned getScale() {
            return m_scale;
        }

        virtual void setScale(unsigned scale) = 0;

        float getOrientation() {
            return m_orientation;
        }
    
    protected:
        unsigned m_oid; //objectid

        float m_orientation;

        unsigned m_scale;

        sf::Vector2f m_position;
};