
// ---INCLUDE---
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>

#include "Geometry.h"
#include "Ray.h"
#include "HitRecord.h"

// ---CODE---

bool Sphere::intersect(const Ray &r, float &t_min, float &closest_t, HitRecord &hit)
{
    // intersection of a ray -> sphere

    // basically a quadratic formula given explained in the manual

    // ax^2 + bx + c = 0
    // from manual p.87 (d·d)t2 + 2d·(e−c)t + (e−c)·(e−c)−R2 =0.

    Eigen::Vector3f ec = r.get_o() - this->get_centre();

    float a = r.get_d().dot(r.get_d());
    float b = 2.0f * (r.get_d().dot(ec));
    float c = ec.dot(ec) - this->get_radius();

    float discrim = (b * b) - (4 * a * c);
    // calculating under square root of grosse bertha

    if (discrim < 0)
    {
        return false;
        // if the discriminant which is under the ssquare root is negative, then mathematically, the equation has no solution, but in context, it just means that the ray does not intersect with the sphere
    };

    float root1 = (-b - sqrt(discrim)) / (2.0f * a);
    float root2 = (-b + sqrt(discrim)) / (2.0f * a);
    // calculating both roots since after the if above, we know the discrim is positive

    float closest_root = 0.0f;

    if (root1 < root2)
    {
        closest_root = root1;
    }
    else
    {
        closest_root = root2;
    };

    if (closest_root < t_min || closest_root > closest_t)
    {
        return false;
        // if the closest_root falls below the minimum (behind the camera) or over the max (behind another object) return false
    };

    hit.set_t(closest_root);
    hit.set_hit_coordinate(r.where_at(closest_root));

    Eigen::Vector3f out_normal = ((hit.get_hit_coordinate() - this->get_centre()) / this->get_radius()).normalized();
    hit.set_snormal(out_normal);
    // calculating the out pointing surface normal of the point where the ray intersects

    return true;
};

void Sphere::test()
{
    std::cout << "Type: " << this->get_type() << std::endl;
    std::cout << "Radius: " << this->get_radius() << std::endl;
    std::cout << "Centre: " << this->get_centre().transpose() << std::endl;
    std::cout << "Phong Coefficient: " << this->get_pc() << std::endl;
};

bool Rectangle::intersect(const Ray &r, float &t_min, float &closest_t, HitRecord &hit)
{

    // same concept as triangle intersection of ray in the manual
    // first, check if it hits the inf plane made by the rectangle
    // then check if it's inside the edges made by the 4 points

    // recall the 4 points are assured to be coplanar and counterclockwise

    float dot_value_ray_normal = this->get_n().dot(r.get_d());
    // dot product can tell us if there's an intersection, if theyre para or perpen

    if (std::abs(dot_value_ray_normal < 1e-6))
    {
        return false;
        // if the dot product is 0, then it means it's para, so the ray will never hit the inf plane
    };

    float t = (this->get_p1() - r.get_o()).dot(this->get_n()) / dot_value_ray_normal;
    // equation for calculating the value t for when the ray hits the inf plane made by the 4 points
    // used dot_value_ray_normal since we're reusing that value, so no need to redo the calc

    if (t < t_min || t > closest_t)
    {
        return false;
        // if t is smaller than our minimum, it's behind the camera
        // if t is bigger than the closest_t, it's behind whatever made closest_t
    };

    Eigen::Vector3f hit_point = r.where_at(t);
    // getting the coordinates of where the intersection happened

    // to check if a point is inside a rectangle, the logic is:
    // for each edge, cross product of edge and hit_point_to_a_corner vector must point in the same direction of the normal
    // if for any edge, it does not, it is not inside the rectangle
    // when i do it for one edge, it's basically which side of the line (edge) is the point
    // then for all 4 edges, if the point is inside the rectangle, the side that the point is for each edge is essentially inside the rectangle made by those 4 edges

    Eigen::Vector3f e1 = this->get_p2() - this->get_p1();
    Eigen::Vector3f cornerhit_vector_1 = hit_point - this->get_p1();
    Eigen::Vector3f check1 = e1.cross(cornerhit_vector_1);
    if (this->get_n().dot(check1) < 0)
    {
        return false;
    };
    // return for if not the same direction
    // for edge 1

    Eigen::Vector3f e2 = this->get_p3() - this->get_p2();
    Eigen::Vector3f cornerhit_vector_2 = hit_point - this->get_p2();
    Eigen::Vector3f check2 = e2.cross(cornerhit_vector_2);
    if (this->get_n().dot(check2) < 0)
    {
        return false;
    };
    // return for if not the same direction
    // for edge 2

    Eigen::Vector3f e3 = this->get_p4() - this->get_p3();
    Eigen::Vector3f cornerhit_vector_3 = hit_point - this->get_p3();
    Eigen::Vector3f check3 = e3.cross(cornerhit_vector_3);
    if (this->get_n().dot(check3) < 0)
    {
        return false;
    };
    // return for if not the same direction
    // for edge 3

    Eigen::Vector3f e4 = this->get_p1() - this->get_p4();
    Eigen::Vector3f cornerhit_vector_4 = hit_point - this->get_p4();
    Eigen::Vector3f check4 = e4.cross(cornerhit_vector_4);
    if (this->get_n().dot(check4) < 0)
    {
        return false;
    };
    // return for if not the same direction
    // for edge 4

    hit.set_t(t);
    hit.set_hit_coordinate(hit_point);
    // record the values once we hit this part since it is inside the rectangle

    return true;
};

void Rectangle::test()
{
    std::cout << "Type: " << this->get_type() << std::endl;
    std::cout << "Points 1->4 : [" << this->get_p1().transpose() << "], [" << this->get_p2().transpose() << "], [" << this->get_p3().transpose() << "], [" << this->get_p4().transpose() << "]" << std::endl;
    std::cout << "Surface normal: [" << this->get_n().transpose() << "]" << std::endl;
    std::cout << "Phong Coefficient: " << this->get_pc() << std::endl;
};