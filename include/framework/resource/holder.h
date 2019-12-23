
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../resource/manager.h"
#include "../util/nonRules.h"

class resourceHolder : public NonCopyable, public NonMovable
{
    public:
        static resourceHolder& get()
        {
            static resourceHolder holder;

            return holder;
        }

        resourceManager<sf::Font> fonts;
        resourceManager<sf::Texture> textures;
        resourceManager<sf::SoundBuffer> soundBuffers;

    private:
        resourceHolder()
            : fonts("fonts", "ttf"), textures("textures", "png"), soundBuffers("sfx", "ogg")
        {

        }
};
/*
resourceHolder::resourceHolder()
    : fonts("fonts", "ttf"), textures("textures", "png"), soundBuffers("sfx", "ogg")
{

}*/