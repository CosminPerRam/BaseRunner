
#pragma once

#include <iostream>

#include "framework/handlers/widget.h"

namespace gui::custom
{
    class text : public gui::widget
    {
    public:
        text(const sf::Vector2f position, const std::string content, std::string resource = "others/gui", sf::IntRect sub = {0, 0, 0, 0}, float scale = 1, float size = 16, const std::string font = "arial")
            : widget(position, resource, sub), m_text(content, resourceHolder::get().fonts.get(font), size)
        {
            m_text.setPosition(position);
        }

        void handle(sf::Event e, const sf::RenderWindow &window)
        {

        }

        void render(sf::RenderTarget &renderer)
        {
            renderer.draw(m_text);
        }

        sf::FloatRect getGlobalBounds()
        {
            return m_text.getGlobalBounds();
        }

        void setScale(float scale)
        {
            m_text.setScale(scale, scale);
        }

    protected:
        sf::Text m_text;
        
    };
}