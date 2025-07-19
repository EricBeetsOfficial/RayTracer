#include <string>

#include "src/utils/color.h"
#include "src/utils/logger.h"

namespace tinyraytracer
{
    class Scene;
    class Camera;
    class Ray;
    class Geometry;
    struct Hit;

    class RayTracer
    {
     public:
        RayTracer (const std::string& name) : _name{name}, _backgroundColor{0.2f, 0.2f, 0.2f} { Logger::message("Run " + name); }

     public:
        virtual Color run     (const Scene& s, std::shared_ptr<Camera> c, const Ray& r, const int& depth) const = 0;
        virtual Color shading (const Scene& s, std::shared_ptr<Camera> c, const Hit& h, const Ray& r, std::shared_ptr<Geometry> g) const;

        std::shared_ptr<Geometry> geometry        (const Scene& s, const Ray& r, Hit& h) const;
        const Color&              backgroundColor ( )                                    const { return _backgroundColor; }

     private:
        std::string _name;
        Color       _backgroundColor;
    };

    class SimpleRayTracer : public RayTracer
    {
     public:
        SimpleRayTracer ( ) : RayTracer("SimpleRayTracer") {}
     public:
        virtual Color run(const Scene& scene, std::shared_ptr<Camera> camera, const Ray& ray, const int& depth) const;
    };

    class SimpleRayTracer_v1 : public RayTracer
    {
     public:
        SimpleRayTracer_v1 ( ) : RayTracer("SimpleRayTracer_v1") {}
     public:
        virtual Color run     (const Scene& s, std::shared_ptr<Camera> c, const Ray& r, const int& d) const;
    };
}
