
#pragma once

#include <framework/handlers/item.h>
#include <framework/handlers/widget.h>
#include <framework/handlers/settings.h>

#include <iostream>

namespace gui::custom
{
    class toolbar : public gui::widget
    {
    public:
        toolbar(sf::Vector2f position, float scale = 1)
            : widget(position, "gui", sf::IntRect(0, 0, 32, 256), scale)
        {
            m_selected = 0;
        }

        void handle(sf::Event e, const sf::RenderWindow& window)
        {
            if(e.type == sf::Event::MouseWheelScrolled)
            {
                if(-e.mouseWheelScroll.delta + m_selected > -1 && -e.mouseWheelScroll.delta + m_selected < 8)
                    m_selected = m_selected + -e.mouseWheelScroll.delta;
            }
        }

        void setScale(float scale)
        {
            m_body.setScale(scale, scale);
        }

        void render(sf::RenderTarget& renderer)
        {
            renderer.draw(m_body);

            sf::CircleShape c;
            c.setRadius(4);
            c.setFillColor(sf::Color::Red);

            c.setPosition(16, settings::resolution::HEIGHT / 3 + 32 * m_selected + 16);
            renderer.draw(c);
        }

    private:
        std::array<item, 8> m_items;
        unsigned m_selected;
    };
}