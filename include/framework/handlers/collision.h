
#pragma once

#include <SFML/Graphics.hpp>

namespace _collision
{
    enum class type {constant, variable};
}

static unsigned cid = 0;

class collision
{
    public:
        collision(unsigned scale, const sf::Vector2f& position, _collision::type type)
            : m_scale(scale), m_position(position), m_type(type), m_bounds(position, {scale, scale})
        {
            m_cid = cid++;
        }

        collision(const collision &src)
            : m_type(src.m_type)
        {
            m_position = src.m_position;
            m_scale = src.m_scale;
            m_bounds = src.m_bounds;
            m_cid = src.m_cid;
        }

        virtual void setPosition(const sf::Vector2f& position) {}
        virtual void setOrientation(const float& orientation) {}
        virtual void setScale(unsigned scale) {}

        sf::Vector2f getPosition() {
            return m_position;
        }

        unsigned getScale() {
            return m_scale;
        }

        float getOrientation() {
            return m_orientation;
        }

        void setBounds(const sf::FloatRect& bounds)
        {
            m_bounds = bounds;
        }

        void updateBounds()
        {
            m_bounds = sf::FloatRect(m_position, {m_scale, m_scale});
        }

        sf::FloatRect getBounds() const
        {
            return m_bounds;
        }  //do custom collision in future

        sf::FloatRect getBounds(sf::Vector2f position) const
        {
            return sf::FloatRect(position, {m_scale, m_scale});
        }

        bool colliding(const sf::FloatRect& obj)
        {
            return m_bounds.intersects(obj);
        }

        unsigned getID()
        {
            return m_cid;
        }

        unsigned type()
        {
            if(m_type == _collision::type::constant)
                return 0;

            return 1;
        }

    protected:
        float m_orientation;

        unsigned m_scale;

        sf::Vector2f m_position;
        sf::Vector2f m_size;

    private:
        sf::FloatRect m_bounds;

        unsigned m_cid; //collisionid

        const _collision::type m_type;
};