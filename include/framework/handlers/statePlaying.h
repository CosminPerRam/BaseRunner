
#pragma once

#include "framework/handlers/state.h"
#include "framework/handlers/gui.h"
#include "custom/gui/button.h"
#include "framework/handlers/game.h"

#include <iostream>

class statePlaying : public state
{
    public:
        statePlaying(Game& game)
            : state(game), m_testMenu(game.getWindow(), 50)
        {
            auto b = std::make_unique<gui::custom::button>();
            b->setText("fuckoff");
            b->setFunction([]() {
                std::cout<<"clicked!"<<std::endl;
            });

            m_testMenu.add(std::move(b));
        }

        void handleEvent(sf::Event e) 
        {
            m_testMenu.handle(e, m_game->getWindow());
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
            m_testMenu.render(renderer);
        }

    private:
        gui::stack m_testMenu;
};