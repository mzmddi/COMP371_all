#ifndef HITRECORD_H
#define HITRECORD_H

// ---INCLUDE---
#include <Eigen/Core>

// ---CODE---

class HitRecord
{

    float t;
    Eigen::Vector3f hit_coordinate;
    Eigen::Vector3f snormal;

public:
    HitRecord() {};

    float get_t() const { return this->t; };
    Eigen::Vector3f get_hit_coordinate() const { return this->hit_coordinate; };
    Eigen::Vector3f get_snormal() const { return this->snormal; };
    // getters for hitrecord

    void set_t(float s) { this->t = s; };
    void set_hit_coordinate(Eigen::Vector3f s) { this->hit_coordinate = s; };
    void set_snormal(Eigen::Vector3f s) { this->snormal = s; };
};

#endif