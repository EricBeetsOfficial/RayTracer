# Description

This is a technical test given during an interview.

**Subject**: Develop a mini ray tracer.

**Input**: XML file containing the description of a scene.

**Output**: Image file in a standard format.

**Detailed description**:

The scene contains:
- A set of geometries positioned absolutely in the world: sphere and plane
- A set of point light sources that cast shadows
- A viewpoint used to compute the output image (position, orientation)

Each geometry defines its material:
- Diffuse color
- Reflection
- Transparency

---

# Build
```
$> git clone https://github.com/EricBeetsOfficial/RayTracer.git
$> cd RayTracer
$> mkdir build
$> cd build
$> cmake -DCMAKE_BUILD_TYPE="Release" ..
$> cmake --build . --config Release
```

# Usage

```
$> ./Release/raytracer.exe ../scenes/scene_cornell_box_v2.xml
```

The output image will be in the `../output` directory

# Scenes

Five scene files have been created for testing.
 - ```./scenes/scene_sphere.xml```
 - ```./scenes/scene_sphere_v2.xml```
 - ```./scenes/scene_cornell_box_v1.xml```
 - ```./scenes/scene_cornell_box_v2.xml```
 - ```./scenes/scene_spheres_v1.xml```
 - ```./scenes/scene_spheres_v2.xml```

| ![Scene1](/output/scene_sphere.jpg) | ![Scene2](/output/scene_sphere_v2.jpg) |
| --- | --- |
| ![Scene3](/output/scene_cornell_box_v1.jpg) | ![Scene4](/output/scene_cornell_box_v2.jpg) |
| ![Scene5](/output/scene_spheres_v1.jpg) | ![Scene6](/output/scene_spheres_v2.jpg) |
