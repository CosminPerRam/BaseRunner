
#pragma once

#include <SFML/Graphics.hpp>

#include <nlohmann/json.hpp>

#include <vector>
#include <iostream>

#include "framework/handlers/entity.h"
#include "framework/handlers/object.h"
#include "framework/handlers/settings.h"

#include "custom/handlers/player.h"
#include "custom/util/files.h"
#include "custom/content/objects/wall.h"
#include "custom/handlers/collisionManager.h"

class level
{
    public:
        level(unsigned scale = 64)
            : m_scale(scale), m_defaultScale(scale), m_player(scale, &m_collisionManager)
        {

        }

        virtual void update(sf::Time deltaTime) = 0;
        virtual void fixedUpdate(sf::Time deltaTime) = 0;

        virtual void handleInput() = 0;

        virtual void render(sf::RenderTarget& renderer) = 0;
        
        virtual void changeScale(unsigned scale) = 0;

        unsigned getScale()
        {
            return m_scale;
        }

        unsigned getDefaultScale()
        {
            return m_defaultScale;
        }

        CollisionManager* getCollisionManager()
        {
            return &m_collisionManager;
        }

    protected:
        CollisionManager m_collisionManager;

        player m_player;

        unsigned m_scale;
        unsigned m_defaultScale;
};