#include "src/utils/color.h"

namespace tinyraytracer
{
    struct Hit;
    class Camera;
    class Light;
    class Material;

    class Shading
    {
     public:
        virtual Color compute (const Hit& hit, std::shared_ptr<Camera> camera, std::shared_ptr<Light> light, std::shared_ptr<Material> m) const = 0;
    };

    class Phong : public Shading
    {
     public:
        virtual Color compute (const Hit& hit, std::shared_ptr<Camera> camera, std::shared_ptr<Light> light, std::shared_ptr<Material> m) const;
    };
}
