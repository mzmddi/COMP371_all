
// ---INCLUDE---
#include "Light.h"

#include <Eigen/Core>
#include <iostream>

// ---CODE---

void AreaLight::test()
{
    std::cout << "Type: " << this->get_type() << std::endl;
    std::cout << "Area Points 1->4 : [" << this->get_p1().transpose() << "], [" << this->get_p2().transpose() << "], [" << this->get_p3().transpose() << "], [" << this->get_p4().transpose() << "]" << std::endl;
};

Eigen::Vector3f AreaLight::calculate_light() {};

void PointLight::test()
{
    std::cout << "Type: " << this->get_type() << std::endl;
    std::cout << "Centre: " << this->get_centre().transpose() << std::endl;
};

Eigen::Vector3f PointLight::calculate_light() {};
