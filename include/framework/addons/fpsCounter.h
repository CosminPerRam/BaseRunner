
#include <SFML/Graphics.hpp>

#include <iostream>

#include "../resource/holder.h"

class fpsCounter
{
    public:
        fpsCounter()
        {
            m_text.move(0, 0);
            m_text.setFillColor({255, 255, 255});
            m_text.setOutlineColor(sf::Color::Black);
            m_text.setOutlineThickness(2);
            m_text.setFont(resourceHolder::get().fonts.get("arial"));
            m_text.setCharacterSize(15);
        }

        void update()
        {
            m_frameCount++;

            if(m_delayTimer.getElapsedTime().asMilliseconds() > 200) {
                m_fps = m_frameCount / m_fpsTimer.restart().asSeconds();
                m_frameCount = 0;
                m_delayTimer.restart();
            }
        }

        void draw(sf::RenderTarget& renderer)
        {
            m_text.setString("FPS: " + std::to_string((int)m_fps));
            renderer.draw(m_text);
        }

    private:
        sf::Text m_text;

        sf::Clock m_delayTimer;
        sf::Clock m_fpsTimer;

        float m_fps = 0;

        unsigned m_frameCount = 0;
};