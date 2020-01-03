
#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "framework/resource/holder.h"

namespace gui
{
    class widget //very straight down widget
    {
    public:
        widget(sf::Vector2f position, std::string resource, sf::IntRect sub, float scale = 1)
            : m_scale(scale), m_position(position), m_size(sub.width, sub.height)
        {
            m_body.setTexture(resourceHolder::get().textures.get(resource));
            m_body.setTextureRect(sub);

            m_body.setTexture(resourceHolder::get().textures.get(resource));
            m_body.setTextureRect(sub);

            m_body.setPosition(position);
            m_body.setScale(scale, scale);
        }

        virtual void handle(sf::Event e, const sf::RenderWindow &window) = 0;
        virtual void render(sf::RenderTarget &renderer) = 0;

        virtual void setScale(float scale) = 0;

        float getScale()
        {
            return m_scale;
        }

    protected:
        sf::Sprite m_body;

        sf::Vector2f m_position;
        sf::Vector2f m_size;

        float m_scale;
    };

    namespace simple
    {
        class text : public sf::Text
        {
        public:
            text(unsigned size, std::string font = "arial", sf::Color fillColor = sf::Color::White)
            {
                setCharacterSize(size);
                setFillColor(fillColor);
                setFont(resourceHolder::get().fonts.get(font));
            }
        };

        class rectangle : public sf::RectangleShape
        {
        public:
            bool isRolledOn(const sf::RenderWindow &window) const
            {
                auto pos = sf::Mouse::getPosition(window);
                return getGlobalBounds().contains((float)pos.x, (float)pos.y);
            }

            bool isClicked(sf::Event e, const sf::RenderWindow &window)
            {
                if (isRolledOn(window))
                {
                    if (e.type == sf::Event::MouseButtonPressed)
                    {
                        return e.mouseButton.button == sf::Mouse::Left;
                    }
                }
                return false;
            }
        };
    }
}