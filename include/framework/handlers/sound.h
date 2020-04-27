
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <iostream>

#include "framework/handlers/state.h"
#include "framework/resource/holder.h"

class SoundEngine : public NonCopyable, public NonMovable   //a very basic sound engine
{                                                           //maybe transform this class usage to be like resourceHolder?
    public:
        SoundEngine(const unsigned& volume = 100, const float& pitch = 1)
            : m_volume(volume), m_pitch(pitch)
        {

        }

        void play(const std::string& bufferName, const sf::Vector3f position = {0, 0, 0})
        {
            this->update();
            sounds.emplace_back(resourceHolder::get().soundBuffers.get(bufferName));
            sounds[sounds.size() - 1].setPosition(position);
            sounds[sounds.size() - 1].play();
        }

        void setVolume(const unsigned& volume)
        {
            this->update();

            m_volume = volume;

            for(sf::Sound& sound : sounds)
                sound.setVolume(volume);
        }

        void setPitch(const float& pitch)
        {
            this->update();

            m_pitch = pitch;

            for(sf::Sound& sound : sounds)
                sound.setPitch(pitch);
        }

        void clear()
        {
            sounds.clear();
        }

    private:
        void update()
        {
            for(auto it = sounds.begin(); it != sounds.end(); )
            {
                if(it->getStatus() != sf::Music::Playing)
                    it = sounds.erase(it);
                else 
                    it++;
            }
        }

        std::vector<sf::Sound> sounds;

        unsigned m_volume;
           float m_pitch;
};