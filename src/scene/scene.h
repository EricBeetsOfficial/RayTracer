#include <string>
#include <vector>

#include "src/geometry/camera.h"

namespace tinyraytracer
{
    class Camera;
    class Light;
    class Geometry;
    class Material;

    class Scene
    {
     public:
        Scene ();
        void load (const std::string& fname);
    
     public:
        std::shared_ptr<Camera>                        camera     ( ) const { return (_cameras.size())?(*_cameras.begin()):nullptr; }
        const std::vector<std::shared_ptr<Light>>&     lights     ( ) const { return _lights;  }
        const std::vector<std::shared_ptr<Geometry>>&  geometries ( ) const { return _geometries; }

     private:
        std::shared_ptr<Material> _getMaterialByName (const std::string& n) const;

     private:
        std::vector<std::shared_ptr<Camera>>    _cameras;
        std::vector<std::shared_ptr<Light>>     _lights;
        std::vector<std::shared_ptr<Geometry>>  _geometries;
        std::vector<std::shared_ptr<Material>>  _materials;
    };
}
