// ---NOTES---
/*
File used for small objects, "commons" lets say
    - camera class
    - ray class
*/

// ---INCLUDE
#include "Eigen/Core"
using Eigen::Vector3f;

// ---CODE---

class ray{
    Vector3f start_;
    Vector3f direction_;

public:
    ray(Vector3f start, Vector3f direction){}
    // constructor cause i am not sure what to do yet and how to use the ray in the code

    Vector3f getStart() const;
    Vector3f getDirection() const;
    // getters. using const so i dont accidentally the value inside the ray

};

class camera{
    float fov_;
    Vector3f lookat_;
    Vector3f up_;

public:
    camera(float fov, Vector3f lookat, Vector3f up){}
    // constructor so i have the option of deciding later how to build the object

    float getFov() const;
    Vector3f getLookat() const;
    Vector3f getUp() const;
    // getters, using const so that i dont accidentally change the value inside the camera

}