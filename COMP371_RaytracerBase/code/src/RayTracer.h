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

struct Ray {
    Vector3f o;
    Vector3f d;
    Ray(Vector3f origin, Vector3f direction) {
        o = origin;
        d = direction;
    };
};

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

    Vector3f w_basis;
    Vector3f u_basis;
    Vector3f v_basis;
    // 3 basis vectors
    // they should be normalised when creating them

    float view_plane_height;
    float view_plane_width;
    // the view plane variables

    Vector3f u_pixel_step;
    Vector3f v_pixel_step;
    // the u and v axis vectors, coefficients used for finding which pixel corresponds to where on the view plane i think

    Vector3f du_pixel_steps;
    Vector3f dv_pixel_steps;
    // using u and v, this is the length in the image world of what is one pixel

    Vector3f view_plane_start;
    Vector3f pixel_start;
    // figuring out where the loops will start at

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
    void create_camera_data();
    Ray create_ray(int j, int i);
};

/*
IMPORTANT NOTES:
revision of errors:
how to do a raytracer with the actual math

*/