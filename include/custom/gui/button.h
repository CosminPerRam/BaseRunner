#pragma once

#include <functional>
#include <iostream>

#include "framework/handlers/gui/widget.h"
#include "custom/gui/displayer.h"

namespace gui
{
    namespace custom
    {
        class button : public gui::custom::displayer
        {
            public:
                button(const sf::Vector2f& size = {256, 64}, const std::string& text = "", sf::Color boxFillColor = sf::Color::Black, 
                    sf::Color boxOutlineColor = sf::Color::Green, sf::Color textFillColor = sf::Color::White, sf::Color textOutlineColor = sf::Color::Black)
                    : displayer(size, text, boxFillColor, boxOutlineColor, textFillColor, textOutlineColor)
                {
                    
                }

                void setFunction(std::function<void(void)> func) {
                    m_function = func;
                }

                void handle(sf::Event e, const sf::RenderWindow& window) {
                    auto pos = sf::Mouse::getPosition(window);

                    switch(e.type) {
                        case sf::Event::MouseButtonPressed:
                            switch(e.mouseButton.button) {
                                case sf::Mouse::Left:
                                    if (m_box.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
                                        m_function();
                                    }

                                default:
                                    break;
                            }

                        default:
                            break;
                    }
                }

            private:
                std::function<void(void)> m_function = [](){};
        };
    }
}