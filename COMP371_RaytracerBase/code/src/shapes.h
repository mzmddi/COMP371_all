// ---NOTES---
/*
parent class shape
children class circle and rectangle
this way they can implement their own interset method, but we can call the same regardless of if it is a sphere or a rectangle
*/

// ---INCLUDES---
#include <string>
#include <Eigen/Core>
using Eigen::Matrix4f;
using Eigen::Vector3f;

//---CODE---

class shape
{
protected:
    string type_;

    float ka_;
    float kd_;
    float ks_;
    Vector3f ka_;
    Vector3f kd_;
    Vector3f ks_;
    float pc_;
    // these are present in all shapes, so im putting it in the parent class
    // but they are all related to color, so im defining them and assigning them a value from the json but,
    //      they wont be used for assignment 3 yet since it does not require color yet.

    Matrix4f transform_ = Matrix4f::Identity();
    // the transform is optional, so it is not always there
    // in order to make sure that the code works regardless if it is there or not,
    //      i assigned to the transform the identity matrix, so that when it is used, it basically does nothing
    //      but transform was extracted from the json, then this wouldnt be an identity matrix, and it would affect the calculations

    virtual string getType() const = "0";
    virtual void extractInformation(const nlohmann::json &j) {};
};

class sphere : public shape
{
    Vector3f center_;
    float radius_;

public:
    sphere() {}
    // all the other methods for this class
    string getType() const override {};
    void extractInformation(const nlohmann::json &j) override {};
};

class rectangle : public shape
{
    Vector3f p1_;
    Vector3f p2_;
    Vector3f p3_;
    Vector3f p4_;

public:
    rectangle() {}
    // All the other methods for this class
    // in the assignmemnt, it says assume all points are coplanar
    string getType() const override {};
    void extractInformation(const nlohmann::json &j) override {};
};
