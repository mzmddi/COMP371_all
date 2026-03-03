// ---NOTES---

// ---INCLUDE---
#include "shapes.h"
#include "json.hpp"
#include <iostream>
#include <string>
#include <Eigen/Dense>
using namespace std;

// ---CODE----

// Sphere methods

string sphere::getType() { return type_; };
void sphere::extractInformation(const nlohmann::json &j)
{
    if (j.contains("type") && j.contains("radius") && j.contains("center") && j.contains("ka") && j.contains("kd") && j.contains("ks") && j.contains("pc") && j.contains("ac") && j.contains("dc") && j.contains("sc"))
    {
        this->type_ = "sphere";
        this->center_ << j["center"][0].get<float>(), j["center"][1].get<float>(), j["center"][2].get<float>();
        this->radius_ = j["radius"].get<float>();
        this->ka_ = j["ka"].get<float>();
        this->kd_ = j["kd"].get<float>();
        this->ks_ = j["ks"].get<float>();
        this->pc_ = j["pc"].get<float>();
        this->ac_ << j["ac"][0], j["ac"][1], j["ac"][2];
        this->dc_ << j["dc"][0], j["dc"][1], j["dc"][2];
        this->sc_ << j["sc"][0], j["sc"][1], j["sc"][2];

        if (j.contains("transform"))
        {
            this->transform_ << j["transform"][0], j["transform"][1], j["transform"][2], j["transform"][3],
                j["transform"][4], j["transform"][5], j["transform"][6], j["transform"][7],
                j["transform"][8], j["transform"][9], j["transform"][10], j["transform"][11],
                j["transform"][12], j["transform"][13], j["transform"][14], j["transform"][15];
        };
    }
    else
    {
        std::cout << "Sphere is missing some mandatory values." << endl;
        exit(0);
    };
};
;
bool sphere::intersect(const Vector3f &o, const Vector3f &d)
{
    Vector3f oc = o - this->center_;
    float a = d.dot(d);
    float b = 2.0f * oc.dot(d);
    float c = oc.dot(oc) - (this->radius_ * this->radius_);
    float underthesquare = b * b - 4 * c;
    // we set up our quadratic equation and we find the part thats under the square

    if (underthesquare < 0)
    {
        // if under the square is negative, it's imaginary # and we dont work with that
        return false;
    };
    float sqr = sqrt(underthesquare);
    float first_t = (-b - sqr) / 2.0f / a;
    float second_t = (-b + sqr) / 2.0f / a;
    // calculating the value under the root

    float small_t = std::min(first_t, second_t);
    float big_t = std::max(first_t, second_t);
    return true;
};
// Rectangle methods
string rectangle::getType() { return type_; };
void rectangle::extractInformation(const nlohmann::json &j)
{
    if (j.contains("type") && j.contains("p1") && j.contains("p2") && j.contains("p3") && j.contains("p4") && j.contains("ka") && j.contains("kd") && j.contains("ks") && j.contains("pc") && j.contains("ac") && j.contains("dc") && j.contains("sc"))
    {
        this->type_ = "rectangle";
        this->p1_ << j["p1"][0].get<float>(), j["p1"][1].get<float>(), j["p1"][2].get<float>();
        this->p2_ << j["p2"][0].get<float>(), j["p2"][1].get<float>(), j["p2"][2].get<float>();
        this->p3_ << j["p3"][0].get<float>(), j["p3"][1].get<float>(), j["p3"][2].get<float>();
        this->p4_ << j["p4"][0].get<float>(), j["p4"][1].get<float>(), j["p4"][2].get<float>();
        this->ka_ = j["ka"].get<float>();
        this->kd_ = j["kd"].get<float>();
        this->ks_ = j["ks"].get<float>();
        this->pc_ = j["pc"].get<float>();
        this->ac_ << j["ac"][0], j["ac"][1], j["ac"][2];
        this->dc_ << j["dc"][0], j["dc"][1], j["dc"][2];
        this->sc_ << j["sc"][0], j["sc"][1], j["sc"][2];

        if (j.contains("transform"))
        {
            this->transform_ << j["transform"][0], j["transform"][1], j["transform"][2], j["transform"][3],
                j["transform"][4], j["transform"][5], j["transform"][6], j["transform"][7],
                j["transform"][8], j["transform"][9], j["transform"][10], j["transform"][11],
                j["transform"][12], j["transform"][13], j["transform"][14], j["transform"][15];
        }
    }
    else
    {
        std::cout << "Rectangle is missing some mandatory values." << endl;
        exit(0);
    };
};
bool rectangle::intersect(const Vector3f &o, const Vector3f &d)
{
    Vector3f e1 = this->p2_ - this->p1_;
    Vector3f e2 = this->p3_ - this->p1_;
    Vector3f n_rec = e1.cross(e2).normalized();

    float deno = n_rec.dot(d);
    // check if the ray is paralelle to the plane or close to paralelle

    if (deno < 1e-5)
    {
        return false;
    };
    float t = -n_rec.dot(o) / deno;

    if (t < 0.00001f)
    {
        return false;
    };
    // if its behind the camera

    Vector3f hp = o + t * d;
    // finding the hit point

    float q1 = (this->p2_ - this->p1_).cross(hp - this->p1_).dot(n_rec);
    float q2 = (this->p3_ - this->p2_).cross(hp - this->p2_).dot(n_rec);
    float q3 = (this->p4_ - this->p3_).cross(hp - this->p3_).dot(n_rec);
    float q4 = (this->p1_ - this->p4_).cross(hp - this->p4_).dot(n_rec);
    // we calculate everything we need for determining if its inside the rectangle or outside of it

    if (q1 * q2 >= 0 && q2 * q3 > 0 && q1 * q4 > 0 && q2 * q4 > 0)
    // the logic here is that if all of them are either all negative or postive, they will all product a positive product
    {
        return true;
    }
    else
    {
        return false;
    };
};
