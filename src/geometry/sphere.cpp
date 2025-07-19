#include "src/geometry/sphere.h"
#include "src/geometry/material.h"
#include "src/raytracer/ray.h"
#include "src/raytracer/hit.h"

using namespace tinyraytracer;
using std::string;


Sphere::Sphere(const string& name, const Vector3f& p, const Vector3f& r) : Geometry(name, p, r)
{
    Logger::debug("Sphere creation " + name);
}

Sphere::~Sphere()
{
    Logger::debug("Sphere destruct " + name());
}

void Sphere::setRadius(float r)
{
    _radius = r;
}

bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) 
{ 
    float discr = b * b - 4 * a * c; 
    if (discr < 0) return false; 
    else if (discr == 0.0f) x0 = x1 = - 0.5f * b / a; 
    else { 
        float q = (b > 0.0f) ? 
            -0.5f * (b + sqrt(discr)) : 
            -0.5f * (b - sqrt(discr)); 
        x0 = q / a; 
        x1 = c / q; 
    } 
    if (x0 > x1) std::swap(x0, x1); 
 
    return true; 
} 

bool Sphere::intersection(const Ray& ray, Hit& hit) const 
{
   Vector3f dist =  position() - ray.origin(); 
   //float B = ray.direction() * dist;
   float B = ray.direction().dot(dist);
   float D = B * B - dist.dot(dist) + _radius * _radius; 
   if (D < 0.0f) 
     return false; 
   float t0 = B - sqrtf(D); 
   float t1 = B + sqrtf(D);
   bool retvalue = false; 
   float t = std::numeric_limits<float>::max();
   if ((t0 > 0.1f) && (t0 < t)) 
   {
     t = t0;
     retvalue = true; 
   } 
   if ((t1 > 0.1f) && (t1 < t)) 
   {
     t = t1; 
     retvalue = true; 
   }

    hit.min_distance = t;
    hit.max_distance = t + 1.0f;
    hit.point = ray.origin() + ray.direction() * hit.min_distance;
    hit.normal = hit.point - position();
    hit.normal.normalize();
    return true;
}

void Sphere::dump() const
{
    Logger::debug("Sphere " + name());
    Logger::debug("  position " + position().str());
    Logger::debug("  rotation " + rotation().str());
    Logger::debug("  radius   " + std::to_string(_radius));
    Logger::debug("  material " + material()->name());
}
