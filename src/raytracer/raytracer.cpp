#include <algorithm>
#include "src/raytracer/raytracer.h"
#include "src/raytracer/hit.h"
#include "src/raytracer/shading.h"
#include "src/raytracer/ray.h"
#include "src/raytracer/effect.h"

#include "src/scene/scene.h"
#include "src/geometry/geometry.h"
#include "src/geometry/material.h"
#include "src/geometry/light/light.h"

#define MAX_DEPTH 4

using namespace tinyraytracer;
using std::string;

std::shared_ptr<Geometry> RayTracer::geometry(const Scene& scene, const Ray& ray, Hit& hit) const
{
    // Parse Geometries
    float nearest = std::numeric_limits<float>::max();
    std::shared_ptr<Geometry> geom = nullptr;
    for_each(scene.geometries().begin(), scene.geometries().end(), [&](std::shared_ptr<Geometry> t) {
            Hit current_hit;
            if (t->intersection(ray, current_hit)) {
                if (current_hit.min_distance < nearest) {
                    nearest = current_hit.min_distance;
                    geom = t;
                    hit = current_hit;
                }
            }
    });
    return geom;
}

Color RayTracer::shading(const Scene& scene, std::shared_ptr<Camera> camera, const Hit& hit, const Ray& ray, std::shared_ptr<Geometry> geom) const
{
    Color final_color{0.0, 0.0, 0.0};
    // Parse Lights
    Phong p;
    auto lights = scene.lights();
    for_each(lights.begin(), lights.end(), [&](std::shared_ptr<Light> light) {
        final_color += effect::phong_shadow(*this, scene, camera, light, geom->material(), hit);
        //final_color += effect::phong(*this, scene, camera, light, geom->material(), hit);
    });
    return final_color;
}

Color SimpleRayTracer::run(const Scene& scene, std::shared_ptr<Camera> camera, const Ray& ray, const int& depth) const
{
    Color final_color{0, 0, 0};

    Hit hit;
    std::shared_ptr<Geometry> geom = geometry(scene, ray, hit);
    if (geom) {
        final_color += shading(scene, camera, hit, ray, geom);
    }
    else {
        final_color = backgroundColor();
    }
    return final_color;
}

Color SimpleRayTracer_v1::run(const Scene& scene, std::shared_ptr<Camera> camera, const Ray& ray, const int& depth) const
{
    Color final_color{0, 0, 0};
    Hit hit;
    std::shared_ptr<Geometry> geom = geometry(scene, ray, hit);
    if (geom) {
        if (((geom->material()->transparency() > 0) || (geom->material()->reflective() > 0)) && (depth < MAX_DEPTH)) {
            Color refraction_color = effect::refraction(*this, scene, camera, ray, hit, geom->material()->transparency(), depth);
            Color reflection_color = effect::reflection(*this, scene, camera, ray, hit, geom->material()->reflective(), depth);
            final_color += (refraction_color + reflection_color) * geom->material()->diffuse();
        }
        else {
            final_color += shading(scene, camera, hit, ray, geom);
        }
    }
    else {
        final_color = backgroundColor();
    }
    return final_color;
}
