// ---NOTES---
/*
 */

// ---INCLUDE---
#include "json.hpp"
#include "shapes.h"
#include "commons.h"

#include <Eigen/Core>
using Eigen::Vector3f;
#include <Eigen/Geometry>

#include <vector>
using namespace std;

// ---CODE---


class RayTracer
{

    const nlohmann::json json_;
    vector<shape *> shapes_;
    // output *output_;
    vector<ray *> rays_;
    std::string filename_;
    float fov_;
    Vector3f lookat_;
    Vector3f up_;
    std::vector<int> size_;
    Vector3f centre_;
    Vector3f bkc_;
    float getFov();
    Vector3f getLookat();
    Vector3f getUp();

    Vector3f w_;
    Vector3f u_;
    Vector3f v_;
    // 3 basis vectors
    // they should be normalised when creating them

public:
    RayTracer(const nlohmann::json &input_j);
    void run();
    // these two methods are the only ones exposed, and since they are the only two used outside
    // of the src directory, they are the only two exposed to the system
    // basically lets consider these two as the APIs of my program, if we consider everything i do as a microprogram inside the bigger program

private:
    void extract();
    // read the json file using the nlohmann thing already provided
    // class method, so same scope as everything in class raytracer, so no need to pass params
    // It is working internally (of the raytracer class), so it won't need outside params injected in
    // end goal -> populate the data structures we need with data from the json

    void test_coding();
    void create_basis_vectors();
};

/*
IMPORTANT NOTES:
revision of errors:
how to do a raytracer with the actual math

*/