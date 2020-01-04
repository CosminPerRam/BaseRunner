
namespace resource
{
    enum gui { NORMAL_BUTTON, TOOLBAR, TOOLBAR_SELECT };

    enum entities { PLAYER, GUARD };

    enum walls { TEST };

    namespace _type
    {
        enum wall { HEAD, BODY, TURNED, THIRD, FOURTH };
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