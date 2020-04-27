
#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "framework/handlers/state.h"
#include "framework/handlers/sound.h"
#include "framework/handlers/settings.h"
#include "../util/nonRules.h"
#include "../addons/fpsCounter.h"

class Game : public NonCopyable, public NonMovable
{
    public:
        Game();

        void run();

        template<typename T, typename... Args>

        void pushState(Args&&... args);
        void pushState(std::unique_ptr<state> f_state)
        {
            std::cout<<"A"<<std::endl;
            m_states.push_back(std::move(f_state));
        }
        void popState()
        {
            m_shouldPop = true;
        }
        void exitGame()
        {
            m_shouldPop = true;
            m_shouldExit = true;
        }

        template<typename T, typename... Args>
        void changeState(Args&&... args);

        const sf::RenderWindow& getWindow() const
        {
            return m_window;
        }

        SoundEngine m_soundEngine;

    private:
        void handleEvent();
        void tryPop();

        state& getCurrentState()
        {
            return *m_states.back();
        }

        sf::RenderWindow m_window;
        std::vector<std::unique_ptr<state>> m_states;

        fpsCounter counter;

        bool m_shouldPop = false;
        bool m_shouldExit = false;
        bool m_shouldChangeState = false;

        std::unique_ptr<state> m_change;
};

template<typename T, typename... Args>
inline void Game::pushState(Args&&... args)
{
    pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template<typename T, typename ...Args>
inline void Game::changeState(Args && ...args)
{
    m_change = std::make_unique<T>(std::forward<Args>(args)...);
    m_shouldPop = true;
    m_shouldChangeState = true;
}
