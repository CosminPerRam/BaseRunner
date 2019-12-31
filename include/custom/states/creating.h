
#pragma once

#include "framework/handlers/state.h"
#include "framework/handlers/gui.h"
#include "framework/handlers/game.h"
#include "framework/util/maths.h"

#include "custom/gui/displayer.h"
#include "custom/handlers/player.h"
#include "custom/content/level.h"
#include "custom/states/stale.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

class _creatinglevel : public level
{
    public:
        _creatinglevel()
        {
            m_player.setPosition({-100, -100});
        }

        void render(sf::RenderTarget& renderer)
        {
            for(auto& it : walls)
                it.render(renderer);

            m_player.render(renderer);
        }

        void changeScale(unsigned scale)
        {
            m_scale = scale;

            for(auto& it : walls)
                it.setScale(scale);

            m_player.setScale(scale);
        }

        void update(sf::Time deltaTime)
        {
            m_player.update(deltaTime);
        }

        void fixedUpdate(sf::Time deltaTime)
        {
            m_player.fixedUpdate(deltaTime);
        }

        void handleInput()
        {
            m_player.handleInput();
        }

        void read(const std::string& name)
        {
            std::string data = files::getFileContent(files::data + "/levels/" + name + ".lvl");
            nlohmann::json json = nlohmann::json::parse(data);

            for(auto it = json["walls"].begin(); it != json["walls"].end(); it++)
            {
                unsigned bid = (*it)["bid"].get<unsigned>();
                sf::Vector2f from = {(*it)["from"][0], (*it)["from"][1]};
                sf::Vector2f to = {(*it)["to"][0], (*it)["to"][1]};

                for(unsigned x = from.x; x <= to.x; x++)
                {
                    for(unsigned y = from.y; y <= to.y; y++)
                    {
                        walls.emplace_back(m_scale, bid, &m_collisionManager, (sf::Vector2u){x, y});
                        //maybe add protection for overlapping?
                    }
                }
            }
        }

        void addWall(unsigned type, const sf::Vector2u& coords)
        {
            walls.emplace_back(m_scale, type, &m_collisionManager, coords);
        }

        void write(const std::string& name)
        {
            for(auto& it : walls)
            {
                sf::Vector2f pos = it.getPosition();
                std::cout<<it.getType()<<" ("<<pos.x<<", "<<pos.y<<")"<<std::endl;
            }
        }

        void clear()
        {
            walls.clear();
        }

    private:
        std::vector<wall> walls;
};

namespace states
{
    class creating : public state
    {
        public:
            creating(Game& game)
                : state(game)
            {
                auto d = std::make_unique<gui::custom::displayer>(sf::Vector2f(128, 32));
                d->setPosition({0, (float)game.getWindow().getSize().y - 32});
                d->setText("making");

                m_stack.add(std::move(d));

                rect.setSize({48, 48});
                rect.setOutlineColor(sf::Color::Green);
                rect.setFillColor(sf::Color::Blue);
            }

            void handleEvent(sf::Event e) 
            {
                m_stack.handle(e, m_game->getWindow());

                sf::Vector2i mousePosition;
                
                switch(e.type)
                {
                    case sf::Event::MouseWheelMoved:
                        if(e.mouseWheel.delta == 1)
                            this->zoom(m_zoom + 0.1);

                        if(e.mouseWheel.delta == -1)
                            this->zoom(m_zoom - 0.1);
                        break;
                    case sf::Event::MouseButtonPressed:
                        mousePosition = sf::Mouse::getPosition(m_game->getWindow());
                        m_level.addWall(m_current, {mousePosition.x / m_level.getScale(), mousePosition.y / m_level.getScale()});
                        std::cout<<mousePosition.x / m_level.getScale()<<"="<<mousePosition.y / m_level.getScale()<<std::endl;
                        break;
                    case sf::Event::KeyPressed:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                        {
                            if(m_current < 2)
                                m_current = m_current + 1;
                        }
                        
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                        {
                            if(m_current > 0)
                                m_current = m_current - 1;
                        }

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                        {
                            m_level.clear();
                        }

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        {
                            m_game->pushState<states::stale>(*m_game);
                        }
                        break;
                    default:
                        break;
                }
            }

            void handleInput()
            {

            }

            void update(sf::Time deltaTime)
            {
                m_level.update(deltaTime);

                if(m_current == 0)
                    rect.setFillColor(sf::Color::Green);
                else if(m_current == 1)
                    rect.setFillColor(sf::Color::Red);
                else 
                    rect.setFillColor(sf::Color::Magenta);

                rect.setPosition({sf::Mouse::getPosition(m_game->getWindow()).x, sf::Mouse::getPosition(m_game->getWindow()).y - 48});
            }

            void fixedUpdate(sf::Time deltaTime)
            {
                m_level.fixedUpdate(deltaTime);
            }

            void render(sf::RenderTarget& renderer)
            {
                m_stack.render(renderer);

                m_level.render(renderer);

                renderer.draw(rect);
            }

            void zoom(float zoom)
            {
                if(zoom < 0.5 || zoom > 1.5)
                    return;

                m_zoom = zoom;

                m_level.changeScale(m_level.getDefaultScale() * zoom);
            }

        private:
            gui::stack m_stack;

            sf::RectangleShape rect;

            _creatinglevel m_level;

            unsigned m_current = 0;

            float m_zoom = 1;
    };
}
