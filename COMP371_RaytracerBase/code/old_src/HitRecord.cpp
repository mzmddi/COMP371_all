// ---NOTES---
/*
This class stores any and all hits from the ray to an object
*/

// ---INCLUDES---
#include <Eigen/Core>
using Eigen::Vector3f;
#include <Eigen/Geometry>
#include <limits>

#include "HitRecord.h"

// ---CODE---

HitRecord::HitRecord(int i, int j)
{
    for (int s = 0; s < i * j; s++)
    {
        Hit h = Hit();
        h.t = std::numeric_limits<float>::infinity();
        this->hit_buffer.push_back(h);
    };
};

void HitRecord::new_hit(int i, int j, float t)
{
    // creates a new hit struct
    // checks if there already is another hit struct at that position
    // if there is, compare t values and keep the smallest
    // if there isnt, add the new one

    if (t == std::numeric_limits<float>::infinity())
    {
        h[i * j].color = Vector3f(1.0f, 1.0f, 1.0f);
        return;
    }
    else
    {
        if (h[i * j].t < t)
        {
            return;
        }
        else
        {
            h[i * j].t = t;
            h[i * j].color = Vector3f(0.0f, 0.0f, 0.0f);
        };
    };
};