#include "src/raytracer/ray.h"
#include "src/utils/logger.h"
#include "src/geometry/camera.h"
#include "src/geometry/matrix4.h"

#ifndef M_PI
#define M_PI 3.141592653589793f
#endif

using namespace tinyraytracer;


Ray::Ray ( ) : _origin{0, 0, 0}, _direction {0, 0, 0}
{
}

Ray::Ray (const Vector3f& origin, const Vector3f& direction) : _origin{origin}, _direction{direction}
{
    _direction.normalize();
}


void Ray::compute (int x, int y, const Camera& camera)
{
    int width = camera.width();
    int height = camera.height();
    float angle  = tan(M_PI * 0.5f * camera.fov() / 180.0f);
    float ratio = width / (float)height;
 
    float dx = (2 * ((x + 0.5f) / width) - 1) * angle * ratio;
    float dy = (1 - 2 * ((y + 0.5f) / height   )) * angle;
    _origin   = Vector3f{0.0f, 0.0f, 0.0f};
    _direction = Vector3f{dx, dy, -1.0f};
    _direction.normalize();

    _origin = camera.invView().mult(origin(), 1.0f);
    _direction = camera.invView().mult(direction(), 0.0f);
    _direction.normalize();
}

void Ray::dump ( ) const
{
    Logger::debug("Ray:");
    Logger::debug(" - origin    :" + _origin.str() );
    Logger::debug(" - direction :" + _direction.str() );
}
