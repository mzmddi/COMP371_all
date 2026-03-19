
// ---INCLUDE---
#include "Geometry.h"

#include <iostream>

// ---CODE---

float Sphere::intersect() {return 0.0f;};

void Sphere::test() {
    std::cout << "Type: " << this->get_type() << std::endl;
    std::cout << "Radius: " << this->get_radius() << std::endl;
    std::cout << "Centre: " << this->get_centre().transpose() << std::endl;
};

float Rectangle::intersect() {return 0.0f;};

void Rectangle::test() {
    std::cout<<"Type:"<<this->get_type()<<std::endl;
    std::cout<<"Points 1->4 : [" << this->get_p1().transpose() << "], [" << this->get_p2().transpose() << "], [" << this->get_p3().transpose() << "], [" << this->get_p4().transpose() << "]" << std::endl;
    std::cout<<"Surface normal: [" <<this->get_n().transpose() << "]" << std::endl; 
};