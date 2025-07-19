#include "src/geometry/plane.h"
#include "src/geometry/material.h"
#include "src/raytracer/ray.h"
#include "src/raytracer/hit.h"

using namespace tinyraytracer;
using std::string;

Plane::Plane(const string& name, const Vector3f& p, const Vector3f& r) : Geometry(name, p, r), _normal{0.0f, 0.0f, 0.0f}, _size(0.0f)
{
    Logger::debug("Plane creation " + name);
}

Plane::~Plane()
{
    Logger::debug("Plane destruct " + name());
}

void Plane::setNormal(const Vector3f& n)
{
    _normal = n;
    _normal.normalize();
}

void Plane::setSize(float s)
{
    _size = s;
}

bool Plane::intersection(const Ray& ray, Hit& hit) const 
{
    //Logger::debug("Intersect Plane");
    Vector3f n = _normal * -1.0f;

    float denom = n.dot(ray.direction());
    if (denom > 1e-6) { 
        Vector3f p = position() - ray.origin();
        float t = p.dot(n) / denom;
        if (t >= 0) {
            hit.point = ray.origin() + ray.direction() * t;
            hit.min_distance = t;
            hit.max_distance = hit.min_distance + 1.0f;
            hit.normal = _normal;
            hit.normal.normalize();
            return true;
        }
        return false;
    }
    return false;
}

void Plane::dump() const
{
    Logger::debug("Plane " + name());
    Logger::debug("  position " + position().str());
    Logger::debug("  rotation " + rotation().str());
    Logger::debug("  normal   " + _normal.str());
    Logger::debug("  size     " + std::to_string(_size));
    Logger::debug("  material " + material()->name());
}
