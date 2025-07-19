#include "src/raytracer/effect.h"

#include "src/raytracer/hit.h"
#include "src/raytracer/ray.h"
#include "src/raytracer/raytracer.h"
#include "src/raytracer/shading.h"
#include "src/geometry/vector3.h"
#include "src/geometry/geometry.h"
#include "src/geometry/material.h"
#include "src/geometry/light/light.h"

using namespace tinyraytracer;

#define BIAS 1e-4f

Color effect::refraction(const RayTracer& rt, const Scene& scene, std::shared_ptr<Camera> camera, const Ray& ray, const Hit& hit, float value, const int& depth)
{
    // Refraction (Snell's law)
    Color refraction_color{0, 0, 0};
    if (value > 0) {
        Vector3f normal = hit.normal;

        float result = 10.0f;
        float n = 1.03f;
        if (ray.direction().dot(normal) > 0) {
            normal = -normal;
            n = 1.0f / n;
        }

        Vector3f N = normal * result;
        float cosI = -N.dot(ray.direction());
        float cosT2 = sqrt(1.0f - n * n * (1.0f - cosI * cosI));
        if (cosT2 > 0.0f) {
            Vector3f refraction_direction = ray.direction() * n + N * (n * cosI - cosT2);
            Ray refraction_ray(hit.point + normal * BIAS, refraction_direction);
            refraction_color = rt.run(scene, camera, refraction_ray, depth + 1) * value;
        }
    }
    return refraction_color;
}


Color effect::reflection(const RayTracer& rt, const Scene& scene, std::shared_ptr<Camera> camera, const Ray& ray, const Hit& hit, float value, const int& depth)
{
    Color reflection_color(0, 0, 0);
    // Reflection
    if (value > 0) {
        Vector3f reflection_direction = ray.direction().reflect(hit.normal);
        reflection_direction.normalize();
        Vector3f reflection_origin = hit.point + hit.normal * BIAS;
        Ray reflection_ray(reflection_origin, reflection_direction);
        reflection_color = rt.run(scene, camera, reflection_ray, depth + 1) * value;
    }
    return reflection_color;
}

Color effect::phong(const RayTracer& rt, const Scene& scene, std::shared_ptr<Camera> camera, std::shared_ptr<Light> light, std::shared_ptr<Material> material, const Hit& hit)
{
    Phong phong;
    return phong.compute(hit, camera, light, material);
}

Color effect::phong_shadow(const RayTracer& rt, const Scene& scene, std::shared_ptr<Camera> camera, std::shared_ptr<Light> light, std::shared_ptr<Material> material, const Hit& hit)
{
    Phong phong;

    if (!light->shadow()) {
        return effect::phong(rt, scene, camera, light, material, hit);
    }

    Color shadow_color(0, 0, 0);

    Vector3f lightDir = light->position() - hit.point;
    lightDir.normalize();
    Ray shadowRay({hit.point + hit.normal * BIAS}, {lightDir});
    Hit shadowHit;
    auto shadowGeom = rt.geometry(scene, shadowRay, shadowHit);
    int shadow = (shadowGeom != nullptr)?1:0;
    if (shadow) {
        if (shadowHit.min_distance > light->position().distance(hit.point)) {
            shadow = false;
        }
    }
    Color color = phong.compute(hit, camera, light, material);
    if (shadow) {
        float t = shadowGeom->material()->transparency();
        shadow_color = color * ( (1.0f - t) * 0.2f + t * 0.4f);
    }
    else {
        shadow_color = color;
    }
    return shadow_color;
}
