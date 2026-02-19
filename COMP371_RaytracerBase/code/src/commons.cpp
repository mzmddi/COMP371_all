// ---NOTES---

// ---INCLUDE---
#include "commons.h"

// ---CODE---

// ray::ray() {}
// constructor implementation for ray

// Vector3f ray::getStart() { return start_; };
// Vector3f ray::getDirection() { return direction_; };
// // getter implementation for ray

float camera::getFov() { return fov_; };
Vector3f camera::getLookat() { return lookat_; };
Vector3f camera::getUp() { return up_; };
void camera::extractInformation(const nlohmann::json &j) {};
// getters for the camera