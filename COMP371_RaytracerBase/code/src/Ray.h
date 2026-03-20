#ifndef RAY_H
#define RAY_H

// ---INCLUDE---
#include <Eigen/Core>

// ---CODE---

class Ray
{
    Eigen::Vector3f o;
    Eigen::Vector3f d;

public:
    Ray() {};

    Eigen::Vector3f get_o() const { return this->o; };
    Eigen::Vector3f get_d() const { return this->d; };
    // getters

    void set_o(Eigen::Vector3f s) { this->o = s; };
    void set_d(Eigen::Vector3f s) { this->d = s; };

    Eigen::Vector3f where_at(float t);
};
#endif