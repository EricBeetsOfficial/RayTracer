#include "src/geometry/transform.h"
#include "src/geometry/geometry.h"

namespace tinyraytracer
{
    class Plane : public Geometry
    {
     public:
        Plane  (const std::string& name, const Vector3f& p, const Vector3f& r);
        ~Plane ( );

     public:
        void setNormal (const Vector3f& n);
        void setSize   (float s);
    
        virtual bool intersection (const Ray& ray, Hit& hit) const;
        virtual void dump         ( )                        const;

     private:
        Vector3f _normal;
        float    _size; 
    };
}


