
#pragma once

#include "framework/handlers/object.h"

static unsigned eid = 0;

class entity : public object
{
    public:
        entity(unsigned scale, CollisionManager* collisionManager, const sf::Vector2f& position)
            : object(scale, position, collisionManager, _collision::type::variable)
        {
            m_eid = eid++;
        }

    protected:
        bool isColliding(sf::Vector2f position)
        {
            return m_collisionManager->colliding(this, position);
        }

    private:
        unsigned m_eid;
};