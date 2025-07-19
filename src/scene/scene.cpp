#include <functional>

#include "src/scene/scene.h"
#include "src/geometry/material.h"
#include "src/geometry/sphere.h"
#include "src/geometry/plane.h"
#include "src/geometry/camera.h"
#include "src/geometry/light/light.h"
#include "src/utils/color.h"
#include "third/tinyxml2.h"

using namespace tinyraytracer;
using namespace tinyxml2;
using std::string;
using std::vector;

Scene::Scene() {}

void Scene::load(const string& fname)
{
    Logger::message("Load scene " + fname);

    XMLDocument doc;
	doc.LoadFile(fname.c_str());
    if(doc.ErrorID() != 0) { 
        throw std::runtime_error("Error: xml read scene '" + fname + "' " + doc.ErrorIDToName(doc.ErrorID()));
    }

    XMLElement *pRoot = doc.FirstChildElement("scene");

    auto tag = [](XMLElement *element, const string& tagName) {
        XMLElement *child = element->FirstChildElement(tagName.c_str());
        if (child == nullptr) {
            throw std::runtime_error("Error: tag name does not exist '" + tagName + "'");
        }
        return child;
    };

    auto text = [tag](XMLElement *element, const string& tagName) {
        XMLElement *child = tag(element, tagName);
        return string(child->GetText());
    };

    auto parseChildren = [](XMLElement *element, std::function<void(XMLElement *, const string&, const string&, const string&)> callback) {
        for (XMLElement *child = element->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {

            if (child->BoolAttribute("enable", false)) {
                XMLElement *positionElement = child->FirstChildElement("position");
                XMLElement *rotationElement = child->FirstChildElement("rotation");
                string str_pos = positionElement?positionElement->GetText():"";
                string str_rot = rotationElement?rotationElement->GetText():"";
                if (callback) {
                    callback(child, child->Attribute("name"), str_pos, str_rot);
                }
                else {
                    throw std::runtime_error("Error: Callback event is empty");
                }
            }
        }
    };

    // Parse Materials
    parseChildren(tag(pRoot, "materials"), [&](XMLElement *element, const string& n, const string& p, const string& r) 
    {
        Color diffuse (text(element, "diffuse"));
        Color specular (text(element, "specular"));
        float shininess = std::stof(text(element, "shininess"));
        float reflective = std::stof(text(element, "reflective"));
        float transparency = std::stof(text(element, "transparency"));
        auto material = std::make_shared<Material>(n);
        material->setDiffuse(diffuse);
        material->setSpecular(specular);
        material->setShininess(shininess);
        material->setTransparency(transparency);
        material->setReflective(reflective);
        _materials.push_back(material);
    }); 

    // Parse Geometries
    parseChildren(tag(pRoot, "geometries"), [&](XMLElement *element, const string& n, const string& p, const string& r) 
    {
        // Create
        GeometryFactory::Type type = GeometryFactory::Type::none;
        if (string(element->Name()).compare("sphere") == 0) type = GeometryFactory::Type::sphere;
        if (string(element->Name()).compare("plane") == 0) type = GeometryFactory::Type::plane;
        auto geometry = GeometryFactory::createGeometry(type, n, p, r);
        // Material
        string materialName = string(element->Attribute("material")).erase(0, 1);
        geometry->setMaterial(_getMaterialByName(materialName));
        // Properties
        auto sphere = std::dynamic_pointer_cast<Sphere>(geometry);
        auto plane = std::dynamic_pointer_cast<Plane>(geometry);
        if (sphere != nullptr) {
            sphere->setRadius(std::stof(text(element, "radius")));
        }
        else if (plane != nullptr) {
            plane->setNormal(Vector3f(text(element, "normal")));
        }
        _geometries.push_back(geometry);
    });

    // Parse Lights
    parseChildren(tag(pRoot, "lights"), [&](XMLElement *element, const string& n, const string& p, const string& r) 
    {
        // Create
        LightFactory::Type type = LightFactory::Type::none;
        if (string(text(element, "type")).compare("point") == 0) type = LightFactory::Type::point;
        if (string(text(element, "type")).compare("spot") == 0) type = LightFactory::Type::spot;
        auto light = LightFactory::createLight(type, n, p, r);
        // Color
        string str_col = text(element, "color");
        Color color{str_col};
        light->setColor(color);
        // Shadow
        bool shadow = (string(text(element, "shadow")).compare("true") == 0)?true:false;
        light->setShadow(shadow);
        //
        _lights.push_back(light);
    });

    // Parse Camera
    parseChildren(tag(pRoot, "cameras"), [&](XMLElement *element, const string& n, const string& p, const string& r) 
    {
        auto camera = std::make_shared<Camera>(n, p, r);
        string str_res = text(element, "resolution");
        std::istringstream ss_res(str_res);
        int w, h;
        ss_res >> w;
        ss_res >> h;
        float fov;
        string str_fov = text(element, "fov");
        std::istringstream ss_fov(str_fov);
        ss_fov >> fov;
        camera->setResolution(w, h);
        camera->setFov(fov);
        _cameras.push_back(camera);
    });

    for_each(_geometries.begin(), _geometries.end(), [](std::shared_ptr<Geometry> geometry)
    {
        geometry->dump();
    });
    for_each(_lights.begin(), _lights.end(), [](std::shared_ptr<Light> light)
    {
        light->dump();
    });
    for_each(_cameras.begin(), _cameras.end(), [](std::shared_ptr<Camera> camera)
    {
        camera->dump();
    });
    for_each(_materials.begin(), _materials.end(), [](std::shared_ptr<Material> material)
    {
        material->dump();
    });
}

std::shared_ptr<Material> Scene::_getMaterialByName(const string& name) const
{
    std::shared_ptr<Material> foundMaterial = nullptr;
    for_each(_materials.begin(), _materials.end(), [&](std::shared_ptr<Material> material)
    {
        if (material->name().compare(name) == 0) {
            foundMaterial = material;
        }
    });
    if (foundMaterial == nullptr) throw std::runtime_error("Error: material name does not exist '" + name + "'");
    return foundMaterial;
}
