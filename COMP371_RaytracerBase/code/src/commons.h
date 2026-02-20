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
#include <vector>
#include <string>

// ---CODE---

class ray
{
public:
    Vector3f origin_;
    Vector3f direction_;
    // before passing to constructure of ray, must do direction.normalize()

    ray(Vector3f origin, Vector3f direction) : origin_(origin), direction_(direction) {}
};

class output
{
public:
    std::string filename_;
    float fov_;
    Vector3f lookat_;
    // where the camera is looking at
    Vector3f up_;
    // world up direcriion
    std::vector<int> size_;
    Vector3f centre_;
    // camera position
    Vector3f bkc_;
    output() {}
    // constructor so i have the option of deciding later how to build the object

    float getFov();
    Vector3f getLookat();
    Vector3f getUp();
    // getters, using const so that i dont accidentally change the value inside the camera

    void extractInformation(const nlohmann::json &j);
};