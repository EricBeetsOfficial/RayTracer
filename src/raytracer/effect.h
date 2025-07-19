#include "src/utils/color.h"

namespace tinyraytracer
{
    class RayTracer;
    class Scene;
    class Camera;
    class Ray;
    struct Hit;
    class Light;
    class Material;

    namespace effect
    {
        Color refraction (const RayTracer& rt, const Scene& s, std::shared_ptr<Camera> c, const Ray& r, const Hit& h, float v, const int& d);
        Color reflection (const RayTracer& rt, const Scene& s, std::shared_ptr<Camera> c, const Ray& r, const Hit& h, float v, const int& d);


        Color phong_shadow (const RayTracer& rt, const Scene& s, std::shared_ptr<Camera> c, std::shared_ptr<Light> l, std::shared_ptr<Material> m, const Hit& h);
        Color phong        (const RayTracer& rt, const Scene& s, std::shared_ptr<Camera> c, std::shared_ptr<Light> l, std::shared_ptr<Material> m, const Hit& h);
    }
}