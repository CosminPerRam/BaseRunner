
#include <SFML/Graphics.hpp>

#include <vector>

class animation
{
    public:
        struct frame
        {
            frame(const sf::IntRect& c_bounds, sf::Time c_delay)
                : bounds(c_bounds), delay(c_delay)
            { }

            sf::IntRect bounds;
            sf::Time    delay;
        };

        animation(unsigned width, unsigned height)
            : f_width(width), f_height(height)
        {

        }

        void add(unsigned index, sf::Time delay)
        {
            sf::IntRect bounds(0, index * f_width, f_width, f_height);

            m_frames.emplace_back(bounds, delay);
        }

        const sf::IntRect& get()
        {
            m_oTime = m_oTime + m_timer.getElapsedTime();

            while(m_oTime >= m_frames[m_framePoint].delay)
            {
                m_oTime = m_oTime - m_frames[m_framePoint].delay;

                m_framePoint++;
            }

            m_timer.restart();

            return m_frames[m_framePoint % m_frames.size()].bounds;
        }

    private:
        sf::Clock m_timer; //progression timer
        sf::Time m_oTime;  //overlapped time

        std::vector<frame> m_frames;

        unsigned m_framePoint = 0;

        const unsigned f_width;
        const unsigned f_height;
};