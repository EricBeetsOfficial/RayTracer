#include "src/geometry/geometry.h"
#include "src/geometry/sphere.h"
#include "src/geometry/plane.h"

using namespace tinyraytracer;
using std::string;

std::shared_ptr<Geometry> GeometryFactory::createGeometry(GeometryFactory::Type type, const std::string& name, const Vector3f& position, const Vector3f& rotation)
{
    switch(type)
    {
        case GeometryFactory::Type::plane:
            return std::make_shared<Plane>(name, position, rotation);
        case GeometryFactory::Type::sphere:
            return std::make_shared<Sphere>(name, position, rotation);
        default:
            throw std::runtime_error("Error: Unknow geometry type...");
            return nullptr;
    }
}