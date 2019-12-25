
#pragma once

#include "framework/handlers/state.h"
#include "framework/handlers/gui.h"
#include "framework/handlers/game.h"

#include "custom/gui/displayer.h"

#include <iostream>

class statePlaying : public state
{
    public:
        statePlaying(Game& game)
            : state(game)
        {
            auto d = std::make_unique<gui::custom::displayer>(sf::Vector2f(128, 32));
            d->setPosition({0, (float)game.getWindow().getSize().y - 32});
            d->setText("making");

            m_stack.add(std::move(d));
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