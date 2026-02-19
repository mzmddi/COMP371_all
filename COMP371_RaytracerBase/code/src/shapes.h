// ---NOTES---
/*
parent class shape
children class circle and rectangle
this way they can implement their own interset method, but we can call the same regardless of if it is a sphere or a rectangle
*/

// ---INCLUDES---
#include <string>
#include <Eigen/Core>
using Eigen::Vector3f;

//---CODE---

class shape {
    public:
        virtual string getType() const = "0";
};

class sphere : public shape {
    string type_;
    Vector3f center_;
    float radius_;
public:
    sphere(string type, Vector3f center, float radius){}
    // all the other methods for this class
    string getType() const override;
};

class rectangle : public shape {
    string type_;
    Vector3f p1_;
    Vector3f p2_;
    Vector3f p3_;
    Vector3f p4_;
public:
    rectangle(string type, Vector3f p1, Vector3f p2, Vector3f p3, Vector3f p4){}
    // All the other methods for this class
    // in the assignmemnt, it says assume all points are coplanar
    string getType() const override;
};
