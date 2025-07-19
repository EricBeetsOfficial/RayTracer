#include "src/geometry/vector3.h"

namespace tinyraytracer
{
    class Camera;

    class Ray
    {
     public:
        Ray ( );
        Ray (const Vector3f& o, const Vector3f& d);

     public:
        void setOrigin    (const Vector3f& o) { _origin = o;    }
        void setDirection (const Vector3f& d) { _direction = d; }

        const Vector3f& origin    ( ) const { return _origin;    }
        const Vector3f& direction ( ) const { return _direction; }

        void dump ( ) const;

     public:
        void compute (int x, int y, const Camera& c);

     private:
        Vector3f _origin;
        Vector3f _direction;
    };
}
