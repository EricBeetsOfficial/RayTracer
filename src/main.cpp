#include "src/scene/scene.h"
#include "src/raytracer/ray.h"
#include "src/raytracer/raytracer.h"

#include "src/image/image.h"
#include "src/utils/logger.h"

#include <filesystem>

using namespace tinyraytracer;

int main(int argc, char *argv[])
{
    Scene scene;
    try {
        if (argc == 2) {
            scene.load(argv[1]);
        }
        else {
            throw std::runtime_error("Error: xml filename is missing: " + std::string(argv[0]) + " <scene.xml>");
        }
    }
    catch(std::exception& e) {
        Logger::error(e.what());
        exit(-1);
    }

    auto camera = scene.camera();
    int width = camera->width();
    int height = camera->height();
    Logger::debug("Camera resolution: " + std::to_string(camera->width()) + "x" + std::to_string(camera->height()));
    Logger::debug("Geometries count : " + std::to_string(scene.geometries().size()));

#if 0
    RayTracer *ray_tracer = new SimpleRayTracer_v1();
    Ray ray({0,0,0}, {0, 0, 0});
    ray.compute(width / 2, height / 2, *camera.get());
    Color color = ray_tracer->run(scene, camera, ray, 0);
    Logger::debug("Middle pixel color : " + color.str());

#else
    Image img(width, height, 3);
    RayTracer *ray_tracer = new SimpleRayTracer_v1();
    // RayTracer *ray_tracer = new SimpleRayTracer();
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            Ray ray({0,0,0}, {0, 0, 0});
            ray.compute(x, y, *camera.get());

            Color color = ray_tracer->run(scene, camera, ray, 0);
            img.setPixel(x, y, color);
        }
    }
    Logger::message("Writing image");
    std::filesystem::create_directories("../output/");
    img.save("../output/" + std::filesystem::path(argv[1]).stem().string());
#endif
}
