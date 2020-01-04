
#pragma once

#include "framework/handlers/object.h"

static unsigned eid = 0;

class entity : public object
{
    public:
        entity(unsigned scale, const sf::Vector2f& position, math::quadPoint bounds, sf::Vector2f drift, CollisionManager* collisionManager)
            : object(scale, position, bounds, collisionManager, drift, _collision::type::variable)
        {
            m_eid = eid++;
        }

    protected:
        bool isColliding(math::quadPoint to)
        {
            return m_collisionManager->colliding(to, this->getID());
        }

    private:
        unsigned m_eid;
};