// ---NOTES---

// ---INCLUDE---
#include "json.hpp"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>

// ---CODE---


class RayTracer{
    public:
        RayTracer(const nlohmann::json& j);
        void run();

    private:
        std::string filename;

        // background color?
        // camera point
        // view direction? -w
        // up direction? v
        // perspective ?? orthogo or orthonormal ??

        // need to make a way to store all the geometries vector<>?
        //  need to define a plane class?
        // need to define a ray class?
        

        // need to find a way to extract the data from the json first then do something with it

        /*
        quick brainstorm:
        1) extract data from json object nlohmann??
        2) input data into the sphere and rectangle class and store them somewhere
        3) extract all the other data from the json that are not the shapes
        4) if we assume we have a ray, implement the math in the methods of each shape for the intersection
        5) structure everyone in the context of the run() method since thats where it is run
        6) output file?
        */

};