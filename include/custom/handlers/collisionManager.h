
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

        unsigned colliding(math::quadPoint obj, unsigned nid)
        {
            for(auto colli : collisions)
            {
                collision* coll = colli.get();
                
                if(coll->colliding(obj) && coll->getID() != nid)
                    return coll->getID();
            }

            return 0;
        }

        unsigned size()
        {
            return collisions.size();
        }

    private:
        std::vector<std::shared_ptr<collision>> collisions;
};