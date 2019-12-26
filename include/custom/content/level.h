
#pragma once

#include <SFML/Graphics.hpp>

#include <nlohmann/json.hpp>

#include <vector>
#include <iostream>

#include "framework/handlers/entity.h"
#include "framework/handlers/object.h"
#include "custom/util/files.h"

#include "custom/content/objects/wall.h"

class level
{
    public:
        level(unsigned scale = 32)
            : m_scale(scale), m_defaultScale(scale)
        {

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
                        walls.emplace_back(m_scale, bid, (sf::Vector2u){x, y});
                        //maybe add protection for overlapping?
                    }
                }
            }
        }

        void addWall(unsigned type, const sf::Vector2u& coords)
        {
            walls.emplace_back(m_scale, type, coords);
        }

        void write(const std::string& name)
        {
            for(auto& it : walls)
            {
                sf::Vector2f pos = it.getPosition();
                std::cout<<it.getType()<<" ("<<pos.x<<", "<<pos.y<<")"<<std::endl;
            }
        }

        void update(sf::Time deltaTime)
        {

        }

        void fixedUpdate(sf::Time deltaTime)
        {

        }
        
        void render(sf::RenderTarget& renderer)
        {
            for(auto& it : walls)
                it.render(renderer);
        }

        void changeScale(unsigned scale)
        {
            m_scale = scale;

            for(auto& it : walls)
                it.setScale(scale);
        }

        unsigned getScale()
        {
            return m_scale;
        }

        unsigned getDefaultScale()
        {
            return m_defaultScale;
        }

        void clear()
        {
            walls.clear();
        }

    private:
        std::vector<wall> walls;

        unsigned m_scale;
        unsigned m_defaultScale;
};