#ifndef HITRECORD_H
#define HITRECORD_H

// ---INCLUDE---
#include <Eigen/Core>

// ---CODE---

class HitRecord
{

    float t;
    Eigen::Vector3f hit_coordinate;

    float ka;
    float kd;
    float ks;
    float pc;
    Eigen::Vector3f ac;
    Eigen::Vector3f dc;
    Eigen::Vector3f sc;
    Eigen::Vector3f n;
    // all the lighting info we need for a hit

public:
    HitRecord() {};

    float get_t() const { return this->t; };
    Eigen::Vector3f get_hit_coordinate() const { return this->hit_coordinate; };
    float get_ka() const { return this->ka; };
    float get_kd() const { return this->kd; };
    float get_ks() const { return this->ks; };
    float get_pc() const { return this->pc; };
    Eigen::Vector3f get_ac() const { return this->ac; };
    Eigen::Vector3f get_dc() const { return this->dc; };
    Eigen::Vector3f get_sc() const { return this->sc; };
    Eigen::Vector3f get_n() const { return this->n; };
    // all getters

    void set_ka(float s) { ka = s; };
    void set_kd(float s) { kd = s; };
    void set_ks(float s) { ks = s; };
    void set_pc(float s) { pc = s; };
    void set_ac(Eigen::Vector3f s) { ac = s; };
    void set_dc(Eigen::Vector3f s) { dc = s; };
    void set_sc(Eigen::Vector3f s) { sc = s; };
    void set_t(float s) { this->t = s; };
    void set_hit_coordinate(Eigen::Vector3f s) { this->hit_coordinate = s; };
    void set_n(Eigen::Vector3f s) { this->n = s; };
    // all the setters for hitrecord
};

#endif