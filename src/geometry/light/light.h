#include "src/geometry/transform.h"
#include "src/utils/color.h"

namespace tinyraytracer
{
    class Light : public Transform
    {
     public:
        Light  (const std::string& name, const Vector3f& p, const Vector3f& r);
        ~Light ( );
    
     public:
        virtual void dump   ( ) const;
        const Color& color  ( ) const { return _color;}
        bool         shadow ( ) const { return _shadow; }

        void setColor  (const Color& c) { _color = c;  }
        void setShadow (bool v)         { _shadow = v; }

     private:
        Color _color;
        bool  _shadow;
    };

    class PointLight : public Light
    {
     public:
        PointLight  (const std::string& name, const Vector3f& p, const Vector3f& r);
        ~PointLight ( ) { }
     };

    namespace LightFactory
    {
        enum Type { none, point, spot };
        std::shared_ptr<Light> createLight(Type, const std::string& name, const Vector3f& p, const Vector3f& r);
    }
}
