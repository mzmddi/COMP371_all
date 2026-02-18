// ---NOTES---
/*
create virtual class. create rect and sphe as children. 
implement their own logic for intersection
but since they share same parent, can be considered as the same class, so used adjacently
if i do intersect as a class method, ill need pass the ray (instance or pointer?) to the method
*/

// ---INCLUDES---
#include <string>
#include <Eigen/core>

//---CODE---

class Shape {
    public:
        std::string type;
        Shape(){};
        // all the methods shared accross the geometries
        // point intersect() ?
};

class Sphere : public Shape {
    public:
        Sphere(std::string type, Eigen::Vector3f center, float radius){};
        // all the other methods for this class
};

class Rectangle : public Shape {

    public:
        Rectangle(std::string type, Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3fp3 p3, Eigen::Vector3f p4 )
        //All the other methods for this class
    };
