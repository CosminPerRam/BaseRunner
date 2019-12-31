
#pragma once

#include "framework/handlers/collision.h"

class CollisionManager
{
    public:
        void add(collision* coll)
        {
            collisions.emplace_back(coll);
        }

        bool colliding(collision* collision, sf::Vector2f position)
        {
            for(auto coll : collisions)
            {
                if(coll->colliding(collision->getBounds(position)) && coll != collision)
                {
                    sf::Vector2f pos = coll->getPosition();
                    std::cout<<pos.x<<" "<<pos.y<<" "<<coll->getScale()<<std::endl;
                    return true;
                }
            }

            return false;
        }

        unsigned size()
        {
            return collisions.size();
        }

    private:
        std::vector<collision*> collisions;
};