
#pragma once

#include <SFML/Graphics.hpp>

namespace graphics
{
    class effect
    {
        public:
            const std::string& getName()
            {
                return m_name;
            }

        protected:
            effect(const std::string& name)
                : m_name(name)
            {

            }

            virtual void onLoad() = 0;

        private:
            std::string m_name;
    };
}