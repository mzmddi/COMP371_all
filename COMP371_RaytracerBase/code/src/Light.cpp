
// ---INCLUDE---
#include "Light.h"
#include "HitRecord.h"
#include "Ray.h"
#include "Geometry.h"

#include <Eigen/Core>
#include <iostream>

// ---CODE---

void AreaLight::test()
{
    std::cout << "Type: " << this->get_type() << std::endl;
    std::cout << "Area Points 1->4 : [" << this->get_p1().transpose() << "], [" << this->get_p2().transpose() << "], [" << this->get_p3().transpose() << "], [" << this->get_p4().transpose() << "]" << std::endl;
};

Eigen::Vector3f AreaLight::calculate_light(HitRecord &closest_hitrecord, const Eigen::Vector3f &light_centre, const Eigen::Vector3f output_ai, const std::vector<Geom *> &geoms) { return Eigen::Vector3f(0.0f, 0.0f, 0.0f); };

void PointLight::test()
{
    std::cout << "Type: " << this->get_type() << std::endl;
    std::cout << "Centre: " << this->get_centre().transpose() << std::endl;
};

Eigen::Vector3f PointLight::calculate_light(HitRecord &closest_hitrecord, const Eigen::Vector3f &light_centre, const Eigen::Vector3f output_ai, const std::vector<Geom *> &geoms)
{
    float t_min = 0.000001f;

    Eigen::Vector3f ambient = (closest_hitrecord.get_ka() * closest_hitrecord.get_ac()).cwiseProduct(output_ai);
    Eigen::Vector3f pixel_color = ambient;
    // we set up the ambient color first

    Eigen::Vector3f dl = (this->get_centre() - closest_hitrecord.get_hit_coordinate()).normalized();
    // setting light direction

    float distance_to_light = (this->get_centre() - closest_hitrecord.get_hit_coordinate()).norm();
    // getting the distance of the light source to the point

    Ray r = Ray();

    r.set_o(closest_hitrecord.get_hit_coordinate());
    r.set_d(dl);
    // using the ray as the shadow ray

    bool is_occluded = false;
    // we're going to use this as a check if the point is occluded or not

    for (auto &geom : geoms)
    {
        // looping through the geometries again to check if the geometry is blocking the light

        float t_shadow;
        // the t of the ray for the shadow ray

        if (geom->intersect(r, t_min, distance_to_light, closest_hitrecord))
        {
            is_occluded = true;
            break;
            // we found that the point is blocked by a geometry from the light
        };
    };

    float n_dot_l = std::max(0.0f, closest_hitrecord.get_n().dot(dl));
    Eigen::Vector3f diffuse = (closest_hitrecord.get_kd() * n_dot_l) * closest_hitrecord.get_dc().cwiseProduct(this->get_id());
    // calculated the diffuse vector for the point

    Eigen::Vector3f V = (light_centre - closest_hitrecord.get_hit_coordinate()).normalized();
    Eigen::Vector3f R = (2.0f * closest_hitrecord.get_n().dot(dl) * closest_hitrecord.get_n() - dl).normalized();
    float v_dot_r = std::max(0.0f, V.dot(R));
    Eigen::Vector3f specular = (closest_hitrecord.get_ks() * pow(v_dot_r, closest_hitrecord.get_pc())) * closest_hitrecord.get_sc().cwiseProduct(this->get_is());
    // calculating the specular vector

    return (diffuse + specular);
};
