#pragma once

#include "src/geometry/vector3.h"
#include "src/utils/logger.h"

namespace tinyraytracer
{
    class Transform
    {
     public:
        Transform(const std::string& n, const Vector3f& p, const Vector3f& r) : _position {std::move(p)},
                                                                                _rotation {std::move(r)},
                                                                                _name     {std::move(n)} {}
        virtual ~Transform ( ) { Logger::debug("Transform destruct " + name()); }
     public:
        const Vector3f&   position ( ) const { return _position; }
        const Vector3f&   rotation ( ) const { return _rotation; }
        const std::string name     ( ) const { return _name;     }
        virtual void      dump     ( ) const = 0;

     private:
        Vector3f    _position;
        Vector3f    _rotation;
        std::string _name;
    };
}
