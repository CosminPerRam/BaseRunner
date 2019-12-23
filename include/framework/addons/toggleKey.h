
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

class toggleKey
{
    public:
        toggleKey(sf::Keyboard::Key key)
            : m_key(key)
        {

        }

        bool isKeyPressed()
        {
            if(m_delayTimer.getElapsedTime().asMilliseconds() > 200)
            {
                if(sf::Keyboard::isKeyPressed(m_key))
                {
                    m_delayTimer.restart();

                    return true;
                }
            }

            return false;
        }

    private:
        sf::Keyboard::Key m_key;
        sf::Clock m_delayTimer;
};