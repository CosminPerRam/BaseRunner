
#pragma once

#include <iostream>

#include "framework/handlers/widget.h"

namespace gui::custom
{
    class displayer : public gui::widget
    {
    public:
        displayer(const sf::Vector2f position, const std::string text = "", const std::string resource = "gui", sf::IntRect sub = sf::IntRect(0, 0, 128, 32), float scale = 1)
            : widget(position, resource, sub, scale), m_text(16)
        {
            m_text.setScale(scale, scale);
            m_text.setString(text);
            m_text.setPosition(position.x + m_size.x / 2 - m_text.getGlobalBounds().width / 2, position.y + m_size.y / 4);
        }

        void setScale(float scale)
        {
            m_body.setScale(scale, scale);
            m_text.setScale(scale, scale);
        }

        void handle(sf::Event e, const sf::RenderWindow &window)
        {

        }

        void render(sf::RenderTarget &renderer)
        {
            renderer.draw(m_body);
            renderer.draw(m_text);
        }

        sf::FloatRect getGlobalBounds()
        {
            return m_body.getGlobalBounds();
        }

    protected:
        gui::simple::text m_text;
    };
} // namespace gui::custom