
#include <iostream>

#include "framework/handlers/game.h"
#include "framework/handlers/statePlaying.h"

Game::Game()
    : m_window ({1280, 720}, "fuckers")
{
    m_window.setPosition({m_window.getPosition().x, 0});
    m_window.setFramerateLimit(60);
    pushState<statePlaying>(*this);
}

void Game::run()
{
    constexpr unsigned TPS = 30;
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
            default:
                break;
        }
    }
}

state& Game::getCurrentState()
{
    return *m_states.back();
}

void Game::pushState(std::unique_ptr<state> f_state)
{
    m_states.push_back(std::move(f_state));
}

void Game::popState()
{
    m_shouldPop = true;
}

void Game::exitGame()
{
    m_shouldPop = true;
    m_shouldExit = true;
}

const sf::RenderWindow& Game::getWindow() const
{
    return m_window;
}

