
#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include <iostream>

#include "framework/handlers/widget.h"
#include "framework/util/nonRules.h"
#include "framework/resource/holder.h"

namespace gui
{
    class stack : public NonCopyable    //very straight down menu
    {
        public:
            ~stack() = default;

            void add(std::unique_ptr<widget> w) {
                m_widgets.push_back(std::move(w));
            }

            void handle(sf::Event e, const sf::RenderWindow& window) //could made this virtual = 0
            {
                for(auto& widget : m_widgets) {
                    widget->handle(e, window);
                }
            }

            void render(sf::RenderTarget& renderer)
            {
                for(auto& widget : m_widgets) {
                    widget->render(renderer);
                }
            }

        private:
            const sf::RenderWindow& getWindow() const {
                return *m_window;
            }

            const sf::RenderWindow* m_window;

            std::vector<std::unique_ptr<widget>> m_widgets;

            sf::Vector2f m_position;
            sf::Vector2f m_size;
    };
};