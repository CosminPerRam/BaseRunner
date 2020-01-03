
#pragma once

#include <framework/handlers/item.h>
#include <framework/handlers/gui/widget.h>
#include <framework/handlers/settings.h>

#include <iostream>

namespace gui::custom
{
    class toolbar : public gui::widget
    {
    public:
        toolbar(sf::Vector2f position)
            : m_position(position)
        {
            m_body.setTexture(resourceHolder::get().textures.get("toolbar"));
            m_body.setPosition(m_position);

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

        void setScale(unsigned scale)
        {
            
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
        sf::Vector2f m_position;

        sf::Sprite m_body;

        std::array<item, 8> m_items;
        unsigned m_selected;
    };
}