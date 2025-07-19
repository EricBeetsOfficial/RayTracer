#include "src/geometry/material.h"
#include "src/utils/logger.h"

using namespace tinyraytracer;
using std::string;

Material::Material(const string& name, const Color& diffuse) : _name{name}, 
                                                               _diffuse{diffuse}, 
                                                               _specular{1.0f, 1.0f, 1.0f},
                                                               _shininess{30.0f},
                                                               _reflective{0.0f}, 
                                                               _transparency{0.0f}
{
}

Material::~Material()
{
    Logger::debug("Material destruct " + name());
}

void Material::dump ( ) const
{
    Logger::debug("Material       " + name());
    Logger::debug("  diffuse      " + _diffuse.str());
    Logger::debug("  reflective   " + std::to_string(_reflective));
    Logger::debug("  transparency " + std::to_string(_transparency));

}
