#include "src/geometry/vector3.h"
#include "src/utils/logger.h"

namespace tinyraytracer
{
    struct Hit
    {
        Hit( ) : point{0, 0, 0}, normal{0, 0 ,0}, min_distance{0}, max_distance{0}  {}
        Hit(const Vector3f& p, const Vector3f& n) : point{p}, normal{n}, min_distance{0}, max_distance{0} {}

        Vector3f point;
        Vector3f normal;
        float min_distance;
        float max_distance;

        void dump ( ) const {
            Logger::debug("Hit : ");
            Logger::debug("  point  : " + point.str());
            Logger::debug("  normal : " + normal.str());
        }
    };
}
