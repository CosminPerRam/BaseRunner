
#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "framework/resource/holder.h"

namespace gui
{
    class widget //very straight down widget
    {
    public:
        virtual void handle(sf::Event e, const sf::RenderWindow &window) = 0;
        virtual void render(sf::RenderTarget &renderer) = 0;

        virtual void setScale(unsigned scale) = 0;

        unsigned getScale()
        {
            return m_scale;
        }

    protected:
        unsigned m_scale;

        sf::Vector2f m_position;
    };

    namespace _simple
    {
        class Text : public sf::Text
        {
        public:
            Text()
            {
                setCharacterSize(25);
                setOutlineColor(sf::Color::Black);
                setFillColor(sf::Color::White);
                setFont(resourceHolder::get().fonts.get("arial"));
            }
        };

        class Rectangle : public sf::RectangleShape
        {
        public:
            bool isRolledOn(const sf::RenderWindow &window) const
            {
                auto pos = sf::Mouse::getPosition(window);
                return getGlobalBounds().contains((float)pos.x, (float)pos.y);
            }

            bool isClicked(sf::Event e, const sf::RenderWindow &window)
            {
                if (isRolledOn(window))
                {
                    if (e.type == sf::Event::MouseButtonPressed)
                    {
                        return e.mouseButton.button == sf::Mouse::Left;
                    }
                }
                return false;
            }
        };
    }
}