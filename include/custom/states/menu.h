
#pragma once

#include "framework/handlers/state.h"
#include "framework/handlers/gui.h"
#include "custom/gui/button.h"
#include "framework/handlers/game.h"

#include <iostream>

class stateMenu : public state
{
    public:
        stateMenu(Game& game)
            : state(game)
        {
            auto b = std::make_unique<gui::custom::button>();
            b->setPosition({400, 200});
            b->setText("fuckoff");
            b->setFunction([&]() {
                std::cout<<"clicked!"<<std::endl;
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