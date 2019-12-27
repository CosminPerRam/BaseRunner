
#include <iostream>

#include "framework/handlers/game.h"
#include "custom/states/menu.h"
#include "custom/states/playing.h"
#include "custom/states/creating.h"

Game::Game()
    : m_window ({settings::resolution::WIDTH, settings::resolution::HEIGHT}, "BaseRunner")
{
    m_window.setPosition({0, 0});
    m_window.setFramerateLimit(240);

    pushState<states::menu>(*this);
}

void Game::run()
{
    constexpr unsigned TPS = 60;
    const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag = sf::Time::Zero;

    while(m_window.isOpen() && !m_states.empty()) {
        auto& state = getCurrentState();

        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        state.handleInput();
        state.update(elapsed);
        counter.update();

        while(lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;
            state.fixedUpdate(elapsed);
        }

        m_window.clear();
        state.render(m_window);
        counter.draw(m_window);
        m_window.display();

        handleEvent();
        tryPop();
    }
}

void Game::tryPop()
{
    if(m_shouldPop) {
        m_shouldPop = false;
        if(m_shouldExit) {
            m_states.clear();
            return;
        }
        else if(m_shouldChangeState) {
            m_shouldChangeState = false;
            m_states.pop_back();

            pushState(std::move(m_change));

            return;
        }

        m_states.pop_back();
    }
}

void Game::handleEvent()
{
    sf::Event e;

    while(m_window.pollEvent(e)) {
        getCurrentState().handleEvent(e);
        switch(e.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
                std::cout<<sf::Mouse::getPosition(m_window).x<<" "<<sf::Mouse::getPosition(m_window).y<<std::endl;
                m_soundEngine.play("click");
                break;
            default:
                break;
        }
    }
}
