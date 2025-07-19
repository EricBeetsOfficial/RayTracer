#pragma once
#include "src/geometry/transform.h"
#include "src/geometry/matrix4.h"

namespace tinyraytracer
{
    class Camera : public Transform
    {
     public:
        Camera  (const std::string& name, const Vector3f& p, const Vector3f& r);
        ~Camera ( );

     public:
        void  setResolution (int w, int h);
        void  setFov        (float f);

     public:
        int   width  ( ) const { return _width;  }
        int   height ( ) const { return _height; }
        float fov    ( ) const { return _fov;    }

        const Matrix4f& view    ( ) const { return _view;    }
        const Matrix4f& invView ( ) const { return _invView; }

        virtual void dump ( ) const;

     private:
        void _viewFromlookAt (const Vector3f& e, const Vector3f& t, const Vector3f& u);
        void _viewFromEulers (const Vector3f& r, const Vector3f& p);


     private:
        int      _width;
        int      _height;
        float    _fov;
        Matrix4f _view, _invView;
    };
}

