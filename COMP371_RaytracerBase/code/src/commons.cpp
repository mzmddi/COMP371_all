// ---NOTES---

// ---INCLUDE---
#include "commons.h"

// ---CODE---

ray::ray(Vector3f start, Vector3f direction) : start_(Vector3f start), direction_(Vector3f direction){}
//constructor implementation for ray

Vector3f getStart() const {return start_};
Vector3f getDirection() const {return direction_};
// getter implementation for ray

camera::camera(float fov, Vector3f lookat, Vector3f up) : fov_(fov), lookat_(lookat), up_(up){};
// constructor for the camera

float camera::getFov() const {return fov_};
Vector3f camera::getLookat() const {return lookat_};
Vector3f camera::getUp() const {return up_};
// getters for the camera