#pragma once

#include <functional>
#include <iostream>

#include "framework/handlers/widget.h"
#include "custom/gui/displayer.h"

namespace gui::custom
{
    class button : public gui::custom::displayer
    {
    public:
        button(const sf::Vector2f position, const std::string text, float scale = 1)
            : displayer(position, text, "gui", sf::IntRect(32, 0, 128, 32), scale)
        {

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

    private:
        std::function<void(void)> m_function = []() {};
    };
} // namespace gui::custom