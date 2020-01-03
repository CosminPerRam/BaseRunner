
#pragma once

#include <SFML/Graphics.hpp>

#include <framework/handlers/collision.h>

#include "custom/handlers/collisionManager.h"

static unsigned oid = 0;

class object : public collision
{
    public:
        object(unsigned scale, const sf::Vector2f& position, math::quadPoint bounds, CollisionManager* collisionManager, _collision::type type = _collision::type::constant)
            : collision(scale, position, bounds, type), m_collisionManager(collisionManager)
        {
            m_oid = oid++;

            if(m_oid != 0)
                m_collisionManager->add(this);
        }

        virtual void update(sf::Time deltaTime) {}
        virtual void fixedUpdate(sf::Time deltaTime) {}
        virtual void render(sf::RenderTarget& renderer) = 0;
    
    protected:
        CollisionManager* m_collisionManager;

        unsigned m_oid; //objectid
};