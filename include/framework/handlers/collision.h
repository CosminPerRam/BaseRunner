
#pragma once

#include <SFML/Graphics.hpp>

namespace _collision
{
    enum class type {constant, variable};
}

class collision
{
    public:
        collision(unsigned scale, const sf::Vector2f& position, _collision::type type)
            : m_scale(scale), m_position(position), m_type(type), m_bounds(position, {scale, scale})
        {
            
        }

        virtual void setPosition(const sf::Vector2f& position) {}
        virtual void setOrientation(const float& orientation) {}
        virtual void setScale(unsigned scale) = 0;

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
            //this->updateBounds();

            return m_bounds.intersects(obj);
        }

    protected:
        float m_orientation;

        unsigned m_scale;

        sf::Vector2f m_position;
        sf::Vector2f m_size;

    private:
        sf::FloatRect m_bounds;

        const _collision::type m_type;
};