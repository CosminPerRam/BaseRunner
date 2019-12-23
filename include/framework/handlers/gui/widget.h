
#include <SFML/Graphics.hpp>

#include <memory>

#include "resource/holder.hpp"

namespace gui
{
    class widget    //very straight down widget
    {
        public:
            virtual void handle(sf::Event e, const sf::RenderWindow& window) = 0;
            virtual void render(sf::RenderTarget& renderer) = 0;

            virtual void setPosition(const sf::Vector2f& pos) = 0;

            virtual sf::Vector2f getSize() const = 0;
    };
}