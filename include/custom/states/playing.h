
#pragma once

#include "framework/handlers/state.h"
#include "framework/handlers/gui.h"
#include "framework/handlers/game.h"
#include "framework/util/maths.h"

#include "custom/gui/displayer.h"
#include "custom/handlers/player.h"
#include "custom/content/level.h"
#include "custom/states/stale.h"

#include <SFML/Graphics.hpp>

#include <iostream>

namespace states
{
    class playing : public state
    {
        public:
            playing(Game& game)
                : state(game), m_player(m_level.getScale())
            {
                auto d = std::make_unique<gui::custom::displayer>(sf::Vector2f(128, 32));
                d->setPosition({0, (float)game.getWindow().getSize().y - 32});
                d->setText("playing");

                m_stack.add(std::move(d));

                m_level.read("test");
            }

            void handleEvent(sf::Event e) 
            {
                m_stack.handle(e, m_game->getWindow());
                
                switch(e.type)
                {
                    case sf::Event::KeyPressed:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        {
                            m_game->pushState<states::stale>(*m_game);
                        }
                        break;
                    default:
                        break;
                }
            }

            void handleInput()
            {
                m_player.handleInput();
                
            }
            void update(sf::Time deltaTime)
            {
                m_level.update(deltaTime);
                m_player.update(deltaTime);
            }
            void fixedUpdate(sf::Time deltaTime)
            {
                m_level.fixedUpdate(deltaTime);
                m_player.fixedUpdate(deltaTime);
            }
            void render(sf::RenderTarget& renderer)
            {
                m_stack.render(renderer);

                m_player.render(renderer);
                m_level.render(renderer);
            }

        private:
            gui::stack m_stack;

            level m_level;
            player m_player;

            unsigned m_scale = 32;
    };
}