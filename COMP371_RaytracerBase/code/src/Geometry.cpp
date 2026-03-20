
// ---INCLUDE---
#include "Geometry.h"

#include <iostream>

// ---CODE---

bool Sphere::intersect(const Ray &r, float &t_min, float &closest_t, HitRecord &hit) {

};

void Sphere::test()
{
    std::cout << "Type: " << this->get_type() << std::endl;
    std::cout << "Radius: " << this->get_radius() << std::endl;
    std::cout << "Centre: " << this->get_centre().transpose() << std::endl;
    std::cout << "Phong Coefficient: " << this->get_pc() << std::endl;
};

bool Rectangle::intersect(const Ray &r, float &t_min, float &closest_t, HitRecord &hit) { return 0.0f; };

void Rectangle::test()
{
    std::cout << "Type: " << this->get_type() << std::endl;
    std::cout << "Points 1->4 : [" << this->get_p1().transpose() << "], [" << this->get_p2().transpose() << "], [" << this->get_p3().transpose() << "], [" << this->get_p4().transpose() << "]" << std::endl;
    std::cout << "Surface normal: [" << this->get_n().transpose() << "]" << std::endl;
    std::cout << "Phong Coefficient: " << this->get_pc() << std::endl;
};