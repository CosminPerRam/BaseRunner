#pragma once

#include <functional>

#include "framework/handlers/gui/widget.h"

namespace gui
{
    namespace custom
    {
        class button : public gui::widget
        {
            public:
                button(const sf::Vector2f& size = {256, 64})
                {
                    m_button.setOutlineColor(sf::Color::Green);
                    m_button.setOutlineThickness(1);
                    m_button.setFillColor(sf::Color::Black);

                    m_button.setSize(size);
                }

                void setFunction(std::function<void(void)> func) {
                    m_function = func;
                }

                void setText(const std::string& string) 
                {
                    m_text.setString(string);
                    updateText();
                }

                void setTexture(const sf::Texture& texture) {
                    m_button.setTexture(&texture);
                }

                void handle(sf::Event e, const sf::RenderWindow& window) {
                    auto pos = sf::Mouse::getPosition(window);

                    switch(e.type) {
                        case sf::Event::MouseButtonPressed:
                            switch(e.mouseButton.button) {
                                case sf::Mouse::Left:
                                    if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
                                        m_function();
                                    }

                                default:
                                    break;
                            }

                        default:
                            break;
                    }
                }

                void render(sf::RenderTarget& renderer)
                {
                    renderer.draw(m_button);
                    renderer.draw(m_text);
                }

                void setPosition(const sf::Vector2f& pos)
                {
                    m_position = pos;

                    m_button.setPosition(m_position);
                    m_text.setPosition(m_position);

                    updateText();
                }

                sf::Vector2f getSize() const {
                    return m_button.getSize();
                }

            private:
                void updateText()
                {
                    m_text.setOrigin(m_text.getGlobalBounds().width  / 2,
                        m_text.getGlobalBounds().height / 2);

                    m_text.move(m_button.getGlobalBounds().width  / 2.0f,
                        m_button.getGlobalBounds().height / 2.5f);
                }

                sf::Vector2f m_position;

                Rectangle m_button;
                Text m_text;
                std::function<void(void)> m_function = [](){};
        };

        inline std::unique_ptr<button> makeButton() {
            return std::make_unique<button>();
        }
    }
}