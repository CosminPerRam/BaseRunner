
#pragma once

#include <SFML/Graphics.hpp>

namespace _collision
{
    enum class type {constant, variable};
}

static unsigned cid = 1;

class collision
{
    public:
        collision(unsigned scale, const sf::Vector2f& position, math::quadPoint bounds, _collision::type type)
            : m_scale(scale), m_position(position), m_type(type), m_localBounds(bounds), m_bounds(quad::toPosition(bounds, position))
        {
            m_cid = cid++;
        }

        collision(const collision &src)
            : m_type(src.m_type)
        {
            m_position = src.m_position;
            m_scale = src.m_scale;
            m_bounds = src.m_bounds;
            m_cid = src.m_cid;
        }

        virtual void setPosition(const sf::Vector2f& position) {}
        virtual void setRotation(const float angle) {}
        virtual void setScale(unsigned scale) {}

        sf::Vector2f getPosition() {
            return m_position;
        }

        unsigned getScale() {
            return m_scale;
        }

        float getRotation() {
            return m_angle;
        }

        void setLocalBounds(const math::quadPoint bounds)
        {
            m_localBounds = bounds;
        }

        void setBounds(const math::quadPoint bounds)
        {
            m_bounds = bounds;
        }

        math::quadPoint getLocalBounds() const
        {
            return m_localBounds;
        }

        math::quadPoint getBounds() const
        {
            return m_bounds;
        }

        bool colliding(math::quadPoint obj)
        {
            math::quadPoint A = this->m_bounds;
            math::quadPoint B = obj;

            float A_min = 0;
            float A_max = 0;
            float B_min = 0;
            float B_max = 0;

            sf::Vector2f normal;
            sf::Vector2f lineSlope;

            for (unsigned i = 0; i < 8; i++)
            {
                A_min = 0;
                A_max = 0;
                B_min = 0;
                B_max = 0;

                if (i < 4)
                {
                    unsigned q = i + 1;
                    if (q >= 4)
                        q = 0;

                    lineSlope = math::slope(A[i], A[q]);

                    normal = sf::Vector2f(-lineSlope.y, lineSlope.x);
                }
                else
                {
                    unsigned q = i - 4 + 1;
                    if (q >= 4)
                        q = 0;
                    lineSlope = math::slope(B[i - 4], B[q]);

                    normal = sf::Vector2f(-lineSlope.y, lineSlope.x);
                }

                A_max = math::projectedPoint(A[0], normal);
                A_min = math::projectedPoint(A[0], normal);

                B_max = math::projectedPoint(B[0], normal);
                B_min = math::projectedPoint(B[0], normal);

                for (unsigned p = 0; p < 8; p++)
                {
                    if (p < 4)
                    {
                        if (math::projectedPoint(A[p], normal) > A_max)
                            A_max = math::projectedPoint(A[p], normal);
                        else if (math::projectedPoint(A[p], normal) < A_min)
                            A_min = math::projectedPoint(A[p], normal);
                    }
                    else
                    {
                        if (math::projectedPoint(B[p - 4], normal) > B_max)
                            B_max = math::projectedPoint(B[p - 4], normal);
                        else if (math::projectedPoint(B[p - 4], normal) < B_min)
                            B_min = math::projectedPoint(B[p - 4], normal);
                    }
                }

                if (B_min > A_max || A_min > B_max)
                    return false;
            }
            return true;
        }

        unsigned getID()
        {
            return m_cid;
        }

        unsigned type()
        {
            if(m_type == _collision::type::constant)
                return 0;

            return 1;
        }

    protected:
        float m_angle;

        unsigned m_scale;

        sf::Vector2f m_position;
        sf::Vector2f m_size;

    private:
        math::quadPoint m_localBounds;
        math::quadPoint m_bounds;

        unsigned m_cid; //collisionid

        const _collision::type m_type;
};