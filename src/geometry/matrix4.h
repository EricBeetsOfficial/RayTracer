#pragma once

#include <vector>

#ifndef M_PI
#define M_PI 3.141592653589793f
#endif


#include "src/geometry/vector3.h"

#define DEG2RAD(deg) ( (deg) * M_PI ) / 180.f;

namespace tinyraytracer
{
    template<typename T>
    class Matrix4
    {
     public:
        Matrix4()
        {
            std::vector<T> v(16, 0);
            _data = v;
            identity();
        }

        Matrix4(T* array)
        {
            init(array);
        }

     public:
        void init(T* array)
        {
            std::vector<T> v(16, 0);
            _data = v;
            for (int i = 0; i < 16; ++i) {
                _data[i] = array[i];
            }
        }

        T operator () (int i, int j) const
        {
            return _data[i * 4 + j];
        }

        Vector3<T> mult (const Vector3<T>& vec, T w) const
        {
            float v[4] = {vec.x(), vec.y(), vec.z(), w};
            float res[4] = {0, 0, 0, 0};
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    res[j] += (*this)(i, j) * v[i];
                }
            }
            Vector3<T> r(res[0], res[1], res[2]);
            return r;
        }

        std::string str()
        {
            std::string out = "";
            for (int i = 0; i < 4; ++i) {
                out += std::to_string((*this)(i, 0)) + " " + std::to_string((*this)(i, 1)) + " " + std::to_string((*this)(i, 2)) + " " + std::to_string((*this)(i, 3)) + "\n";
            }
            return out;
        }

        void eulerXYZ(const Vector3<T>& r, const Vector3<T>& p)
        {
            T A = DEG2RAD(r.x());
            T B = DEG2RAD(r.y());
            T C = DEG2RAD(r.z());

            T m[16] = {
                  cos(B) * cos(C)                           , -cos(B) * sin(C)                           ,  sin(B)         , p.x(),
                  sin(A) * sin(B) * cos(C) + cos(A) * sin(C), -sin(A) * sin(B) * sin(C) + cos(A) * cos(C), -sin(A) * cos(B), p.y(),
                 -cos(A) * sin(B) * cos(C) + sin(A) * sin(C),  cos(A) * sin(B) * sin(C) + sin(A) * cos(C),  cos(A) * cos(B), p.z(),
                0                                           ,  0                                         ,  0              , 1};
            init(m);
        }

        void lookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up)
        {
            Vector3<T> zaxis = eye - target;          // forward
            zaxis.normalize();
            Vector3<T> xaxis = up.cross(zaxis);       // right
            xaxis.normalize();
            Vector3<T> yaxis = zaxis.cross(xaxis);    // up
            yaxis.normalize();

            T m[16] = {
                xaxis.x(),        yaxis.x(),        zaxis.x(),        0,
                xaxis.y(),        yaxis.y(),        zaxis.y(),        0,
                xaxis.z(),        yaxis.z(),        zaxis.z(),        0,
                -xaxis.dot(eye ), -yaxis.dot(eye ), -zaxis.dot(eye ), 1};
            init(m);
        }

        void transpose()
        {
            std::vector<T> v(16, 0);
            v = _data;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    v[i * 4 + j] = (*this)(j, i);
                }
            }
            _data = v;
        }

        void identity()
        {
            _data[0] = _data[5] = _data[10] = _data[15] = 1.0f;
        }

        void inverse()
        {
            T inv[16];

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    inv[j * 4 + i] = _invf(i, j , _data.data());

            T D = 0;

            for(int k = 0; k < 4; k++) D += _data[k] * inv[k*4];

            if (D == 0.0f) return;

            D = 1.0f / D;

            for (int i = 0; i < 16; i++)
                _data[i] = inv[i] * D;
        }

     private:
        T _invf(int i,int j, const T* m)
        {
            int o = 2 + (j - i);

            i += 4 + o;
            j += 4 - o;

            #define e(a,b) m[ ((j + b) % 4) * 4 + ((i + a) % 4) ]
            float inv =
             + e(+1, -1) * e(+0, +0) * e(-1, +1)
             + e(+1, +1) * e(+0, -1) * e(-1, +0)
             + e(-1, -1) * e(+1, +0) * e(+0, +1)
             - e(-1, -1) * e(+0, +0) * e(+1, +1)
             - e(-1, +1) * e(+0, -1) * e(+1, +0)
             - e(+1, -1) * e(-1, +0) * e(+0, +1);

            return (o % 2)? inv : -inv;
            #undef e
        }
     private:
        std::vector<T> _data;
    };
    typedef Matrix4<float> Matrix4f;
}