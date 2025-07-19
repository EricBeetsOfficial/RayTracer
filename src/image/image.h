#include <vector>
#include <string>

namespace tinyraytracer
{
    struct Color;

    class Image
    {
     public:
        Image ( );
        Image (int w, int h, int b);
 
     public:
        void        setPixel (int x, int y, const Color& c);
        const Color getPixel (int x, int y) const;

     public:
        void save (const std::string& fname);

     private:
        int _width;
        int _height;
        int _bpp;
        std::vector<unsigned char> _pixels;
    };
}
