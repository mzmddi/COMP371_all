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

    float ka;
    float kd;
    float ks;
    float pc;
    Eigen::Vector3f ac;
    Eigen::Vector3f dc;
    Eigen::Vector3f sc;
    // all the lighting info we need for a hit

public:
    HitRecord() {};

    float get_t() const { return this->t; };
    Eigen::Vector3f get_hit_coordinate() const { return this->hit_coordinate; };
    Eigen::Vector3f get_snormal() const { return this->snormal; };
    float get_ka() const { return ka; };
    float get_kd() const { return kd; };
    float get_ks() const { return ks; };
    float get_pc() const { return pc; };
    Eigen::Vector3f get_ac() const { return ac; };
    Eigen::Vector3f get_dc() const { return dc; };
    Eigen::Vector3f get_sc() const { return sc; };
    void set_ka(float s) { ka = s; };
    void set_kd(float s) { kd = s; };
    void set_ks(float s) { ks = s; };
    void set_pc(float s) { pc = s; };
    void set_ac(Eigen::Vector3f s) { ac = s; };
    void set_dc(Eigen::Vector3f s) { dc = s; };
    void set_sc(Eigen::Vector3f s) { sc = s; };
    // getters for hitrecord

    void set_t(float s) { this->t = s; };
    void set_hit_coordinate(Eigen::Vector3f s) { this->hit_coordinate = s; };
    void set_snormal(Eigen::Vector3f s) { this->snormal = s; };
};

#endif