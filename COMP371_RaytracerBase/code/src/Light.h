#ifndef LIGHT_H
#define LIGHT_H

// ---INCLUDE---

#include <Eigen/Core>


// ---CODE---


class Light {

    std::string type;
    // type of the light

    Eigen::Vector3f id;
    Eigen::Vector3f is; 
    //diffuse and specular light intensity

    Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
    int n;
    bool usecenter;
    //optional options from the json



public:

    Light() {};
    // constructor for virtual class

    

};





#endif