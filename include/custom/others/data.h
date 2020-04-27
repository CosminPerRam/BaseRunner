
#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <tuple>

typedef std::tuple<std::string, std::string, sf::IntRect> resdat;

namespace resource
{
    namespace content
    {
        namespace gui
        {
             const resdat NORMAL_BUTTON = {"GUI_NORMAL_BUTTON", "others/gui", {32, 0, 128, 32}};
                   const resdat TOOLBAR = {"GUI_TOOLBAR", "others/gui", {0, 0, 32, 256}};
            const resdat TOOLBAR_SELECT = {"GUI_TOOLBAR_SELECT", "others/gui", {32, 32, 32, 32}};
        }

        namespace entities
        {
            const resdat PLAYER = {"ENTITY_PLAYER", "others/gui", {0, 0, 2, 3}};
             const resdat GUARD = {"ENTITY_GUARD", "others/gui", {0, 0, 2, 3}};
        }

        namespace walls
        {
            const resdat TEST = {"WALL_TEST", "others/gui", {0, 0, 2, 3}};
        }
    }

    namespace handle
    {
        namespace player
        {
            const unsigned BOUNDS_WIDTH = 48;
            const unsigned BOUNDS_HEIGHT = 32;
        }
    }
/*
    namespace type
    {
        enum wall { HEAD, BODY, TURNED, THIRD, FOURTH };
    }*/
}
