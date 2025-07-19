#include "src/utils/color.h"
#include "src/image/image.h"
#include "src/utils/logger.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "third/stb_image_write.h"

using namespace tinyraytracer;
using std::string;

Image::Image()
{
}

Image::Image(int width, int height, int bpp) : _width  {width},
                                               _height {height},
                                               _bpp    {bpp}
{
    _pixels = std::vector<unsigned char>(width * height * bpp);
}

void Image::setPixel(int x, int y, const Color& color)
{
    unsigned char *pixel = _pixels.data() + (y * _width + x) * _bpp;
    *(pixel++) = color.ucr();
    *(pixel++) = color.ucg();
    *(pixel++) = color.ucb();
//    if (_bpp == 4) {
//        *(pixel++) = color.a();
//    }
}

const Color Image::getPixel (int x, int y) const
{
    unsigned char r, g, b;//, a;
    const unsigned char *pixel = _pixels.data() + (y * _width + x) * _bpp;
    r = std::min((unsigned char)255, *(pixel++));
    g = std::min((unsigned char)255, *(pixel++));
    b = std::min((unsigned char)255, *(pixel++));
//     if (_bpp == 4) {
//        a = std::min((unsigned char)255, *(pixel++));
//    }
    return Color(r, g, b);
}

void Image::save (const string& fname)
{
    int rtn = 0;
    if (_bpp == 3) {
        rtn = stbi_write_jpg(string(fname + ".jpg").c_str(), _width, _height, _bpp, _pixels.data(), _width * _bpp);
    }
    else if (_bpp == 4) {
        rtn = stbi_write_png(string(fname + ".png").c_str(), _width, _height, _bpp, _pixels.data(), _width * _bpp);
    }
    if (rtn == 0)
        Logger::error("Failed to write output image " + fname);
    else
        Logger::message("Write image to " + fname);
}

