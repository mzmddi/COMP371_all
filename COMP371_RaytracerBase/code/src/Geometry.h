#ifndef GEOMETRY_H
#define GEOMETRY_H

// ---INCLUDE---

#include <Eigen/Core>


// ---CODE---

class Geom {

    std::string type;
    // type of the geometry
    // mandatory

    float ka;
    float kd;
    float ks;
    // ambient, diffuse, specular reflection coefficient
    // mandatory

    float pc;
    // phong coefficient
    // mandatory

    Eigen::Vector3f ac;
    Eigen::Vector3f dc;
    Eigen::Vector3f sc;
    // ambient, diffuse, specular reflection color (rgb)
    // mandatory

    Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
    // affine transformation matrix in row major representation
    // optional
    // initialized as an identity matrix so that i can use it regardless if the json file input defines it or not
    // if the json file does not define this, then it will stay an identity matrix, and the computations with this wont change anything

public:
    
    Geom() {}; 
    // constructor for virtual class

    std::string get_type() const {return type;}
    float get_ka() const {return ka;}
    float get_kd() const {return kd;}
    float get_ks() const {return ks;}
    float get_pc() const {return pc;}
    Eigen::Vector3f get_ac() const {return ac;}
    Eigen::Vector3f get_dc() const {return dc;}
    Eigen::Vector3f get_sc() const {return sc;}
    Eigen::Matrix4f get_transform() const {return transform;}
    // all of the getters defined and implement in one shot

    void set_type(std::string s) {type = s;}
    void set_ka(float s) {ka = s;}
    void set_kd(float s) {kd = s;}
    void set_ks(float s) {ks = s;}
    void set_pc(float s) {pc = s;} 
    void set_ac(Eigen::Vector3f s) {ac = s;}
    void set_dc(Eigen::Vector3f s) {dc = s;}
    void set_sc(Eigen::Vector3f s) {sc = s;}
    void set_transform(Eigen::Matrix4f s) {transform = s;}
    // all of the setters defined and implemented 

    virtual float intersect() = 0;
    // virtual methods that ill implement in the child classes

    float get_radius() {return 0.0f;};
    Eigen::Vector3f get_centre() {return Eigen::Vector3f(0.0f, 0.0f, 0.0f);};
    // Eigen::Vector3f get_p1(); 
    // Eigen::Vector3f get_p2() ;
    // Eigen::Vector3f get_p3();
    // Eigen::Vector3f get_p4();
    // Eigen::Vector3f get_n();
    // declarations so i can call these from Geoms

    virtual ~Geom() = default; 
    // destructor for the virtual class
};

class Sphere : public Geom {

    float radius;
    Eigen::Vector3f centre;
    // members specifically for spheres

public:

    Sphere() : Geom() {};

    float get_radius() const {return radius;}
    Eigen::Vector3f get_centre() const {return centre;}
    // additional getters for sphere since not present in parent class

    void set_radius(float s) {radius = s;}
    void set_centre(Eigen::Vector3f s) {centre = s;}
    // additional setters for sphere

    float intersect() override;
    // intersection for sphere specifically
};

class Rectangle : public Geom {

    Eigen::Vector3f p1;
    Eigen::Vector3f p2;
    Eigen::Vector3f p3;
    Eigen::Vector3f p4;
    // 4 corners of the rectangle in counterclockwise order with respect to the normal. 4 points assumed to be coplanar.
    // (from the assignment pdf document) 

    Eigen::Vector3f n;
    // surface normal of the rectangle
    // not given to use from the json, but will eventually be calculated
 
public:

    Rectangle() : Geom() {};

    Eigen::Vector3f get_p1() const {return p1;}
    Eigen::Vector3f get_p2() const {return p2;}
    Eigen::Vector3f get_p3() const {return p3;}
    Eigen::Vector3f get_p4() const {return p4;}
    Eigen::Vector3f get_n() const {return n;}
    // all the additional getters for rec

    void set_p1(Eigen::Vector3f s) {p1 = s;}
    void set_p2(Eigen::Vector3f s) {p2 = s;}
    void set_p3(Eigen::Vector3f s) {p3 = s;}
    void set_p4(Eigen::Vector3f s) {p4 = s;}
    void set_n(Eigen::Vector3f s) {n = s;}
    // additional setters for rec

    float intersect() override;
    // intersect with rec
};




#endif