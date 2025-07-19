#pragma once

#include <memory>
#include "src/geometry/transform.h"
#include "src/utils/logger.h"

namespace tinyraytracer
{
    class Material;
    class Ray;
    struct Hit;

    class Geometry : public Transform
    {
     public:
        Geometry          (const std::string& n, const Vector3f& p, const Vector3f& r) : Transform(n, p, r) { }
        virtual ~Geometry ( ) { Logger::debug("Geometry destruct "); }
 
     public:
        virtual bool intersection (const Ray& ray, Hit& hit) const = 0;

      public:
        void                      setMaterial (std::shared_ptr<Material> m) { _material = m;    }
        std::shared_ptr<Material> material    ( ) const                     { return _material; }

     private:
        std::shared_ptr<Material> _material;
    };

    namespace GeometryFactory
    {
        enum Type { none, sphere, plane };
        std::shared_ptr<Geometry> createGeometry(Type, const std::string& name, const Vector3f& p, const Vector3f& r);
    }
}