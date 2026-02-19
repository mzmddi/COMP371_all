// ---NOTES---

// ---INCLUDE---
#include "shapes.h";

// ---CODE----

// Sphere methods

sphere::sphere(string type, Vector3f center, float radius) : type_(type), center_(center), radius_(radius){};
sphere::getType() const override {return type_};

// Rectangle methods
rectangle::rectangle(string type, Vector3f p1, Vector3f p2, Vector3f p3, Vector3f p4) : type_(type), p1_(p1), p2_(p2), p3_(p3), p4_(p4);
rectangle::getType() const override {return type_};