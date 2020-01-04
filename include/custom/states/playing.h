
#pragma once

#include "framework/handlers/state.h"
#include "framework/handlers/gui.h"
#include "framework/handlers/game.h"
#include "framework/util/maths.h"

#include "custom/gui/text.h"
#include "custom/handlers/player.h"
#include "custom/content/level.h"
#include "custom/states/stale.h"
#include "custom/content/objects/wall.h"
#include "custom/gui/toolbar.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

class _playinglevel : public level
{
    public:
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

                for(auto itt = (*it)["at"].begin(); itt != (*it)["at"].end(); itt++)
                {
                    sf::Vector2u at = {(*itt)[0].get<unsigned>(), (*itt)[1].get<unsigned>()};

                    walls.emplace_back(m_scale, bid, &m_collisionManager, at);
                }
            }

            std::cout<<"Walls: "<<walls.size()<<std::endl;
        }

    private:
        std::vector<wall> walls;
};

namespace states
{
    class playing : public state
    {
        public:
            playing(Game& game)
                : state(game)
            {
                m_stack.add(std::make_unique<gui::custom::text>(sf::Vector2f(0, (float)game.getWindow().getSize().y - 32), "playing"));
                m_stack.add(std::make_unique<gui::custom::toolbar>(sf::Vector2f({0, settings::resolution::HEIGHT / 3})));

                m_level.read("test");
            }

            void handleEvent(sf::Event e) 
            {
                m_stack.handle(e, m_game->getWindow());
                
                switch(e.type)
                {
                    case sf::Event::KeyPressed:
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
                m_level.handleInput();
            }
            void update(sf::Time deltaTime)
            {
                m_level.update(deltaTime);
            }
            void fixedUpdate(sf::Time deltaTime)
            {
                m_level.fixedUpdate(deltaTime);
            }
            void render(sf::RenderTarget& renderer)
            {
                m_level.render(renderer);

                m_stack.render(renderer);
            }

        private:
            gui::stack m_stack;

            _playinglevel m_level;

            unsigned m_scale = 32;
    };
}