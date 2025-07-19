#include "src/geometry/camera.h"
#include "src/utils/logger.h"

using namespace tinyraytracer;
using std::string;

Camera::Camera(const string& name, const Vector3f& p, const Vector3f& r) : Transform(name, p, r), _width{0}, _height{0}, _fov{60.0f}
{
    Logger::debug("Camera creation " + name);

    _viewFromEulers(r, -p);
    //_viewFromlookAt({6, 6, 0}, {0, 0, -20}, {0, 1, 0});
    Logger::debug("View:");
    Logger::debug("\n" + _view.str());
    Logger::debug("Inv:");
    Logger::debug("\n" + _invView.str());
}

Camera::~Camera()
{
    Logger::debug("Camera destruct " + name());
}

void Camera::setResolution(int w, int h)
{
    if ((w < 0) || (h < 0)) throw std::runtime_error("Error: Negative camera resolution");
    _width = w;
    _height = h;
}

void Camera::setFov(float fov)
{
    if (fov < 0) throw std::runtime_error("Error: Negative camera fov");
    _fov = fov;
}

void Camera::dump() const
{
    Logger::debug("Camera " + name());
    Logger::debug("  position   " + position().str());
    Logger::debug("  rotation   " + rotation().str());
    Logger::debug("  resolution " + std::to_string(_width) + ", " + std::to_string(_height));
}

void Camera::_viewFromEulers(const Vector3f& rotation, const Vector3f& position)
{
    _view.eulerXYZ(rotation, position);
    _invView.eulerXYZ(rotation, position);
    _invView.transpose();
    _invView.inverse();
}

void Camera::_viewFromlookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up)
{
    _view.lookAt(eye, target, up);
    _invView.lookAt(eye, target, up);
    _invView.inverse();
}