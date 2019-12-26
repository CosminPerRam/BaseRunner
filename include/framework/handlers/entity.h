
#pragma once

#include "framework/handlers/object.h"

static unsigned eid = 0;

class entity : public object
{
    public:
        entity(unsigned scale, const sf::Vector2f& position)
            : object(scale, position)
        {
            m_eid = eid++;
        }

    private:
        unsigned m_eid;
};