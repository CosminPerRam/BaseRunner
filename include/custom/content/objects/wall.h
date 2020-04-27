
#pragma once

#include "framework/handlers/object.h"

#include <iostream>

class wall : public object
{
    public:
        wall(unsigned scale, unsigned type, CollisionManager* collisionManager, const sf::Vector2u& position)
            : object(scale, sf::Vector2f({position.x * scale, position.y * scale}), 
                {sf::Vector2f({0, 0}), sf::Vector2f({scale, 0}), sf::Vector2f({scale, scale}), sf::Vector2f({0, scale})}, collisionManager), m_type(type)
        {
            m_body.setTexture(resourceHolder::get().textures.get("tiles/walls/test"));
            m_body.setTextureRect({0, 0, 32, 32});
            m_body.setPosition({scale * position.x, scale * position.y});
            m_body.setScale(scale / 32, scale / 32);

            this->setBounds(quad::toPosition(this->getLocalBounds(), {position.x, position.y}));
        }

        void render(sf::RenderTarget& renderer)
        {
            renderer.draw(m_body);
        }

        void setPosition(const sf::Vector2u& position)
        {
            
        }

        unsigned getType()
        {
            return m_type;
        }

        void setScale(unsigned scale)
        {
            m_body.setScale({scale, scale});
            m_body.setPosition({m_position.x / m_scale * scale, m_position.y / m_scale * scale});

            m_scale = scale;
        }

    private:
        unsigned m_type;
};

/*
{ 
    "walls":[
        {
            "bid": 1,
            "at": [[2, 2], [3, 2], [5, 2], [6, 2], [7, 2]]
        },
        {
            "bid": 2,
            "at": [[1, 2], [1, 3], [1, 4]]
        }
    ],
    "tiles":[
        {
            "bid": 1,
            "at": [[3,3]]
        }
    ]
}
*/