#include <string>

#include "src/utils/color.h"

namespace tinyraytracer
{
    class Material 
    {
     public:
        Material  (const std::string& name, const Color& d = Color{1.0f, 1.0f, 1.0f});
        ~Material ( );

     public:
        const std::string& name ( ) const { return _name; }
        void               dump ( ) const;

     public:
        void setDiffuse      (const Color& d) { _diffuse      = d; }
        void setSpecular     (const Color& s) { _specular     = s; }
        void setShininess    (float s)        { _shininess    = std::max(s, 1.0f); }
        void setTransparency (float t)        { _transparency = clamp(t, 0.0f, 1.0f); }
        void setReflective   (float r)        { _reflective   = clamp(r, 0.0f, 1.0f); }

     public:
        const Color& diffuse      ( ) const { return _diffuse;      }
        const Color& specular     ( ) const { return _specular;     }
        float        shininess    ( ) const { return _shininess;    }
        float        transparency ( ) const { return _transparency; }
        float        reflective   ( ) const { return _reflective;   }

     private:
        std::string _name;
        Color       _diffuse;
        Color       _specular;
        float       _shininess;
        float       _reflective;
        float       _transparency;

     private:
        inline float clamp(float x, float a, float b)
        {
            return x < a ? a : (x > b ? b : x);
        }
    };
}
