#pragma once

#include <sstream>
#include <string>
#include <cmath>

namespace tinyraytracer
{
    template<typename T>
    class Vector3
    {
     public:
        Vector3 ( )                      : _x{0}, _y{0}, _z{0} { }
        Vector3 (T x, T y, T z)          : _x{x}, _y{y}, _z{z} { }
        Vector3 (const std::string& str) : _x{0}, _y{0}, _z{0} {
            std::stringstream ss(str);
            ss >> _x;
            ss >> _y;
            ss >> _z;
        }
     public:
        T x() const { return _x; }
        T y() const { return _y; }
        T z() const { return _z; }

        Vector3<T> operator - (const Vector3<T> &v) const
        {
            return Vector3<T>(x() - v.x(), y() - v.y(), z() - v.z());
        }

        Vector3<T> operator - () const 
        {
            return Vector3<T>(-_x, -_y, -_z); 
        }
        
        Vector3<T> operator + (const Vector3<T> &v) const
        {
            return Vector3<T>(x() + v.x(), y() + v.y(), z() + v.z());
        }

        Vector3<T> operator * (const T& v) const
        {
            return Vector3<T>(x() * v, y() * v, z() * v);
        }
        
        void normalize()
        {
            float length = std::sqrt(_x * _x + _y * _y + _z * _z);
            _x /= length;
            _y /= length;
            _z /= length;
        }

        std::string str() const
        {
            return std::to_string(x()) + ", " + std::to_string(y()) + ", " + std::to_string(z());
        }

        Vector3<T> reflect(const Vector3<T>& n) const
        {
            return *this - n * n.dot(*this) * 2.0f;
        }
        T dot(const Vector3<T> &v) const 
        { 
            return x() * v.x() + y() * v.y() + z() * v.z(); 
        }

        Vector3<T> cross(const Vector3<T>& v) const
        {
            return Vector3<T>(y() * v.z() - z() * v.y(), 
                              z() * v.x() - x() * v.z(),
                              x() * v.y() - y() * v.x());
        }

        T distance(const Vector3<T>& v) const
        {
            Vector3<T> dif = Vector3<T>(_x - v.x(), _y - v.y(), _z - v.z());
            return std::sqrt(dif.x() * dif.x() + dif.y() * dif.y() + dif.z() * dif.z());
        }

     private:
        T _x;
        T _y;
        T _z;
    };
    typedef Vector3<float> Vector3f;
}
