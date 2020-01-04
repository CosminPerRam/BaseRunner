#pragma once

#include <functional>
#include <iostream>

#include "framework/handlers/widget.h"
#include "custom/gui/text.h"

namespace gui::custom
{
    class button : public text
    {
    public:
        button(const sf::Vector2f position, const std::string content, const std::string resource = "others/gui", sf::IntRect sub = sf::IntRect(32, 0, 128, 32), float scale = 1)
            : text(position, content, resource, sub, scale)
        {
            m_text.setPosition(position.x + m_size.x / 2 - m_text.getGlobalBounds().width / 2, position.y + m_size.y / 4);
        }

        void render(sf::RenderTarget &renderer)
        {
            renderer.draw(m_body);
            renderer.draw(m_text);
        }

        void setFunction(std::function<void(void)> func)
        {
            m_function = func;
        }

        void handle(sf::Event e, const sf::RenderWindow &window)
        {
            auto pos = sf::Mouse::getPosition(window);

            switch (e.type)
            {
            case sf::Event::MouseButtonPressed:
                switch (e.mouseButton.button)
                {
                case sf::Mouse::Left:
                    if (m_body.getGlobalBounds().contains((float)pos.x, (float)pos.y))
                        m_function();
                default:
                    break;
                }

            default:
                break;
            }
        }

        sf::FloatRect getGlobalBounds()
        {
            return m_body.getGlobalBounds();
        }

        void setScale(float scale)
        {
            m_body.setScale(scale, scale);
            m_text.setScale(scale, scale);
        }

    private:
        std::function<void(void)> m_function = []() {};
    };
} // namespace gui::custom