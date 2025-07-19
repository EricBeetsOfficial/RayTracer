cmake_minimum_required (VERSION 3.30)

project(raytracer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(raytracer src/main.cpp 
                         src/scene/scene.cpp 
                         src/image/image.cpp
                         src/geometry/camera.cpp 
                         src/geometry/geometry.cpp 
                         src/geometry/sphere.cpp 
                         src/geometry/plane.cpp 
                         src/geometry/light/light.cpp 
                         src/geometry/material.cpp 
                         src/raytracer/ray.cpp 
                         src/raytracer/raytracer.cpp 
                         src/raytracer/shading.cpp 
                         src/raytracer/effect.cpp 
                         src/utils/logger.cpp 
                         third/tinyxml2.cpp)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
