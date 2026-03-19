#ifndef LIGHT_H
#define LIGHT_H

// ---INCLUDE---
#include <Eigen/Core>

// ---CODE---

class Light
{

    std::string type;
    // type of the light

    Eigen::Vector3f id;
    Eigen::Vector3f is;
    // diffuse and specular light intensity

    Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
    int n = 1;
    bool usecenter = false;
    bool use = true;
    // optional options from the json

public:
    Light() {};
    // constructor for virtual class

    std::string get_type() const { return this->type; };
    Eigen::Vector3f get_id() const { return this->id; };
    Eigen::Vector3f get_is() const { return this->is; };
    Eigen::Matrix4f get_transform() const { return this->transform; };
    int get_n() const { return this->n; };
    bool get_usecenter() const { return this->usecenter; };
    bool get_use() const { return this->use };
    // all the getters

    void set_type(std::string s) { this->type = s; };
    void set_id(Eigen::Vector3f s) { this->id = s; };
    void set_is(Eigen::VEctor3f s) { this->s = s; }:
    void set_transform(Eigen::Matrix4f s) {this->transform = s;};
    void set_n(int s) { this->n = 1; };
    void set_usecenter(bool s) { this->usecenter = s; };
    void set_use(bool s) { this->use = s };
    // all the setters

    virtual void test() = 0;
    // virtual method for testing

    virtual ~Light() = default;
    // destructor
};

class AreaLight : public Light
{

    Eigen::Vector3f p1;
    Eigen::Vector3f p2;
    Eigen::Vector3f p3;
    Eigen::Vector3f p4;
    // 4 corners of the area light

public:
    AreaLight() : Light() {};

    Eigen::Vector3f get_p1() const { return this->p1; };
    Eigen::Vector3f get_p2() const { return this->p2; };
    Eigen::Vector3f get_p3() const { return this->p3; };
    Eigen::Vector3f get_p4() const { return this->p4; };
    // getters for this specific

    void set_p1(Eigen::Vector3f s) { this->p1 = s; };
    void set_p2(Eigen::Vector3f s) { this->p2 = s; };
    void set_p3(Eigen::Vector3f s) { this->p3 = s; };
    void set_p4(Eigen::Vector3f s) { this->p4 = s; };
    // setters for the area light

    void test() override;
};

class PointLight : public Light
{
    Eigen::Vector3f centre;

public:
    PointLight() : Light() {};

    Eigen::Vector3f get_centre() const { return this->centre; };
    void set_centre(Eigen::Vector3f s) { this->centre = s; };
    // getter and setter for this class
    // since it's just one mandatory value unqiue to point light, it's one getter/setter

    void test() override;
};

#endif