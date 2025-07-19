#include "src/raytracer/shading.h"
#include "src/raytracer/ray.h"
#include "src/raytracer/hit.h"
#include "src/geometry/material.h"
#include "src/geometry/camera.h"
#include "src/geometry/light/light.h"

using namespace tinyraytracer;

Color Phong::compute(const Hit& hit, std::shared_ptr<Camera> camera, std::shared_ptr<Light> light, std::shared_ptr<Material> material) const
{
    // Diffuse
    Vector3f l = light->position() - hit.point;
    Vector3f n = hit.normal;
    l.normalize();
    n.normalize();
    float nl = std::fmax(n.dot(l), 0.0f);
    // Specular
    Vector3f r = l.reflect(n);
    Vector3f v = (hit.point - camera->position());
    r.normalize();
    v.normalize();
    float rv = std::fmax(r.dot(v), 0.0f);
    // Phong
    return (material->diffuse() * light->color() * nl) + material->specular() * pow(rv, material->shininess());
}