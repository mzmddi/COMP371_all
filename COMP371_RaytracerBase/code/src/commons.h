// ---NOTES---
/*
File used for small objects, "commons" lets say
    - camera class
    - ray class
*/

// ---INCLUDE
#include "Eigen/Core"
using Eigen::Vector3f;
#include "json.hpp"

// ---CODE---

class ray
{

public:
    ray() {}
};

class camera
{
    float fov_;
    Vector3f lookat_;
    Vector3f up_;

public:
    camera() {}
    // constructor so i have the option of deciding later how to build the object

    float getFov();
    Vector3f getLookat();
    Vector3f getUp();
    // getters, using const so that i dont accidentally change the value inside the camera

    void extractInformation(const nlohmann::json &j);
};