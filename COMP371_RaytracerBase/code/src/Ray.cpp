
// ---INCLUDE---
#include <Eigen/Core>

#include "Ray.h"

// ---CODE---

Eigen::Vector3f Ray::where_at(float t) const
{
    return (this->get_o() + (t * this->get_d()));
};
// calculate where the ray is at when we check for value t