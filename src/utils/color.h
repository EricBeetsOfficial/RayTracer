#pragma once
#include <sstream>
#include <string>
#include <algorithm>

namespace tinyraytracer
{
    struct Color
    {
     public:
        Color (float r = 0, float g = 0, float b = 0) : _r{r}, _g{g}, _b{b} {}
        Color (const std::string& str)  : _r{0}, _g{0}, _b{0} {
            std::stringstream ss(str);
            float r, g, b;
            ss >> r;
            ss >> g;
            ss >> b;
            _r = r;
            _g = g;
            _b = b;
        }
     public:
        float r() const { return _r; }
        float g() const { return _g; }
        float b() const { return _b; }

        unsigned char ucr() const { return (unsigned char)(std::min(1.0f, _r) * 255); }
        unsigned char ucg() const { return (unsigned char)(std::min(1.0f, _g) * 255); }
        unsigned char ucb() const { return (unsigned char)(std::min(1.0f, _b) * 255); }

        std::string str() const
        {
            return std::to_string(r()) + ", " + std::to_string(g()) + ", " + std::to_string(b());
        }

        Color operator + (const Color& c) const
        {
            return Color(r() + c.r(), g() + c.g(), b() + c.b());
        }

        Color& operator += (const Color& c)
        {
            *this = *this + c;
            return *this;
        }

    
        Color operator * (float v) const
        {
            return Color (r() * v, g() * v, b() * v);
        }

        Color operator * (const Color& c) const
        {
            return Color (r() * c.r(), g() * c.g(), b() * c.b());
        }

     private:
        float _r;
        float _g;
        float _b;
    };
}
