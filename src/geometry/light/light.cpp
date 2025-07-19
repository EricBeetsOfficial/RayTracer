#include "src/geometry/light/light.h"
#include "src/utils/logger.h"

using namespace tinyraytracer;
using std::string;

std::shared_ptr<Light> LightFactory::createLight(LightFactory::Type type, const std::string& name, const Vector3f& position, const Vector3f& rotation)
{
    switch(type)
    {
        case LightFactory::Type::point:
            return std::make_shared<PointLight>(name, position, rotation);
        case LightFactory::Type::spot:
            throw std::runtime_error("Error: Spot light type not yet implemented");
            return nullptr;
        default:
            throw std::runtime_error("Error: Unknow light type...");
            return nullptr;
    }
}


Light::Light(const string& name, const Vector3f& p, const Vector3f& r) : Transform(name, p, r)
{
    Logger::debug("Light creation " + name);
}

Light::~Light()
{
    Logger::debug("Light destruct " + name());
}

void Light::dump() const
{
    Logger::debug("Light " + name());
    Logger::debug("  position " + position().str());
    Logger::debug("  rotation   " + rotation().str());
    Logger::debug("  color      " + color().str());
}

PointLight::PointLight (const std::string& name, const Vector3f& p, const Vector3f& r) : Light(name, p, r) {}

