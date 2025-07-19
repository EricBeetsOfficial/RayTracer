#include "src/geometry/transform.h"
#include "src/geometry/geometry.h"

namespace tinyraytracer
{
    class Sphere : public Geometry
    {
     public:
        Sphere  (const std::string& name, const Vector3f& p, const Vector3f& r);
        ~Sphere ( );

     public:
        virtual bool intersection (const Ray& ray, Hit& hit) const;
        virtual void dump         ( ) const;

        void setRadius (float r);

     private:
        float    _radius;
    };
}
