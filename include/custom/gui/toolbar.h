
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
        toolbar(sf::Vector2f position, float scale = 1, resdat data = resource::content::gui::TOOLBAR)
            : widget(position, std::get<1>(data), std::get<2>(data), scale)
        {
            m_selected = 0;

            m_selectedBody.setTexture(resourceHolder::get().textures.get(std::get<1>(resource::content::gui::TOOLBAR_SELECT)));
            m_selectedBody.setTextureRect(std::get<2>(resource::content::gui::TOOLBAR_SELECT));

            m_selectedBody.setPosition(position);
            m_selectedBody.setScale(scale, scale);
        }

        void handle(sf::Event e, const sf::RenderWindow& window)
        {
            if(e.type == sf::Event::MouseWheelScrolled)
            {
                if(-e.mouseWheelScroll.delta + m_selected > -1 && -e.mouseWheelScroll.delta + m_selected < 8)
                {
                    m_selected = m_selected + -e.mouseWheelScroll.delta;
                    m_selectedBody.setPosition(m_position + (sf::Vector2f(0, 32 * m_scale) * (float)m_selected));
                }
            }
        }

        void setScale(float scale)
        {
            m_body.setScale(scale, scale);
        }

        void render(sf::RenderTarget& renderer)
        {
            renderer.draw(m_body);
            renderer.draw(m_selectedBody);
        }

    private:
        std::array<item, 8> m_items;
        unsigned m_selected;

        sf::Sprite m_selectedBody;
    };
}