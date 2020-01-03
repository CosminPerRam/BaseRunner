
#pragma once

#include <iostream>

#include "framework/handlers/gui/widget.h"

namespace gui::custom
{
    class displayer : public gui::widget
    {
    public:
        displayer(const sf::Vector2f &size, const std::string &text = "", sf::Color boxFillColor = sf::Color::Black,
                sf::Color boxOutlineColor = sf::Color::Green, sf::Color textFillColor = sf::Color::White, sf::Color textOutlineColor = sf::Color::Black)
            : m_size(size)
        {
            m_box.setSize(size);
            m_box.setOutlineThickness(1);
            m_box.setOutlineColor(boxOutlineColor);
            m_box.setFillColor(boxFillColor);

            m_text.setString(text);
            m_text.setFillColor(textFillColor);
            m_text.setOutlineColor(textOutlineColor);
        }

        void setScale(unsigned scale)
        {

        }

        void handle(sf::Event e, const sf::RenderWindow &window)
        {

        }

        void setText(const std::string &text)
        {
            m_text.setString(text);
            updateText();
        }

        void setTextSize(unsigned size)
        {
            m_text.setCharacterSize(size);
        }

        void setTextFillColor(sf::Color textFillColor)
        {
            m_text.setFillColor(textFillColor);
        }

        void setTextOutlineColor(sf::Color textOutlineColor)
        {
            m_text.setOutlineColor(textOutlineColor);
        }

        void setBoxFillColor(sf::Color boxFillColor)
        {
            m_box.setFillColor(boxFillColor);
        }

        void setBoxOutlineColor(sf::Color boxOutlineColor)
        {
            m_box.setOutlineColor(boxOutlineColor);
        }

        void setTexture(const sf::Texture &texture)
        {
            m_box.setTexture(&texture);
        }

        void render(sf::RenderTarget &renderer)
        {
            renderer.draw(m_box);
            renderer.draw(m_text);
        }

        void setPosition(const sf::Vector2f &pos)
        {
            m_position = pos;

            m_box.setPosition(m_position);
            m_text.setPosition(m_position);

            this->updateText();
        }

    private:
        void updateText()
        {
            m_text.setPosition(m_position.x + m_size.x / 2 - m_text.getGlobalBounds().width / 2,
                            m_position.y + m_size.y / 2 - m_text.getGlobalBounds().height / 1.5);
        }
        
        sf::Vector2f m_size;

    protected:
        gui::_simple::Rectangle m_box;
        gui::_simple::Text m_text;
    };
} // namespace gui::custom