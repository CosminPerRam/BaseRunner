
#pragma once

#include "framework/handlers/collision.h"

#include <memory>

class CollisionManager
{
    public:
        void add(collision* coll)
        {
            collisions.push_back(std::make_shared<collision>(*coll));
        }

        bool colliding(collision* f_collision, sf::Vector2f position)
        {
            for(auto colli : collisions)
            {
                collision* coll = colli.get();
                if(coll->colliding(f_collision->getBounds(position)) && coll != f_collision)
                {
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
        std::vector<std::shared_ptr<collision>> collisions;
};