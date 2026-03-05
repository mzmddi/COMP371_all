// ---NOTES---
/*
This class stores any and all hits from the ray to an object
*/

// ---INCLUDES---
#include <Eigen/Core>
using Eigen::Vector3f;
#include <Eigen/Geometry>
#include <vector>

// ---CODE---

struct Hit{
    // hit struct will just store the meta data of a hit, if it occurs
    // more than one hit can occure for the same pixel, hence why save the hit and not just the first one
    
    float t;
    // distance from centre to the shape it has hit

    int j, i;
    // the pixel this hit corresponds to

    Vector3f normal;
    // the normal of the surface the ray hit?
    // i think we'll need this later

    Vector3f color;
    // the color of this pixel hit

};

class HitRecord {
    std::vector<Hit> hit_buffer;
    // holding all the hits

public:
    HitRecord();
    void insert_new_hit();
};