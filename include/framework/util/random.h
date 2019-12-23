
#include <random>
#include <ctime>

template <typename engine = std::mt19937>
class random
{
    template<typename T>

    using uniformDist = std::uniform_real_distribution<T>;
    using uniformIntDist = std::uniform_int_distribution<int>;

    public:
        static Random gRand;

        Random(int seed = std::time(nullptr))
            : m_prng(seed)
        {

        }

        int getIntInRange(int low, int high) {
            return getNumberInRange<uniformIntDist>(low, high);
        }

        float getFloatInRange(float low, float high) {
            return getNumberInRange<uniformDist<float>>(low, high);
        }

        template<typename T>
        T getNumberInRange(T low, T high) {
            return getNumberInRange<uniformDist<T>>(low, high);
        }

        template<typename Dist, typename T>
        T getNumberInRange(T low, T high)
        {
            Dist dist(low, high);

            return dist(m_prng);
        }

    private:
        engine m_prng;
};