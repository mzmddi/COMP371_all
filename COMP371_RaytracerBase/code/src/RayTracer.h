#ifndef RAYTRACER_H
#define RAYTRACER_H

// ===INCLUDE===
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "json.hpp"
#include "Geometry.h"
#include "Light.h"
#include "Output.h"

#include <vector>

// ---CODE---

class RayTracer
{

    const nlohmann::json json_obj;
    // variable holding the json object passed from main.cpp

    std::vector<Geom *> geoms;
    std::vector<Light *> lights;

public:
    RayTracer(const nlohmann::json &input_j);
    void run();

    // no need for setters or getters since everything will be under the scope the RayTracer class

private:
    void test();
    void extract_data();
};

#endif

/*
geometry => type, ka, kd, ks, pc, ac, dc, sc
light => type, id, is
output => filename, size, fov, centre, up, lookat, ai, bkc

*/