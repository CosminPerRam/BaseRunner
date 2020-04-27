
#pragma once

#include "framework/handlers/state.h"
#include "framework/handlers/gui.h"
#include "custom/gui/button.h"
#include "framework/handlers/game.h"

#include "custom/states/menu.h"

#include <iostream>

namespace states
{
    class menu;

    class stale : public state
    {
        public:
            stale(Game& game)
                : state(game)
            {
                auto b = std::make_unique<gui::custom::button>(sf::Vector2f(settings::resolution::WIDTH / 3 + 64, settings::resolution::HEIGHT / 3), "exit");
                b->setFunction([&]() {
                    game.exitGame();
                });

                m_stack.add(std::move(b));

                b = std::make_unique<gui::custom::button>(sf::Vector2f(settings::resolution::WIDTH / 3 + 64, settings::resolution::HEIGHT / 3 + 32), "to menu");
                b->setFunction([&]() {
                    game.changeState<states::menu>(game);
                });

                m_stack.add(std::move(b));

                b = std::make_unique<gui::custom::button>(sf::Vector2f(settings::resolution::WIDTH / 3 + 64, settings::resolution::HEIGHT / 3 + 64), "resume");
                b->setFunction([&]() {
                    game.popState();
                });

                m_stack.add(std::move(b));
            }

            void handleEvent(sf::Event e) 
            {
                m_stack.handle(e, m_game->getWindow());
            }

            void handleInput()
            {

            }

            void update(sf::Time deltaTime)
            {
                
            }

            void fixedUpdate(sf::Time deltaTime)
            {

            }

            void render(sf::RenderTarget& renderer)
            {
                m_stack.render(renderer);
            }

        private:
            gui::stack m_stack;
    };
}