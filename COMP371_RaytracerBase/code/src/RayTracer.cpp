

// ---INCLUDE---

#include "RayTracer.h"

#include <iostream>

// ---CODE---

RayTracer::RayTracer(const nlohmann::json &input_j) : json_obj(input_j) {};

void RayTracer::extract_data(){

    if (this->json_obj.contains("geometry") && (this->json_obj.size() >= 1)) {

        for (const auto& g : this->json_obj["geometry"]) {
            Geom* geo = nullptr;

            if (g["type"] == "sphere") {

                Sphere *s = new Sphere();

                s->set_radius(float(g["radius"]));
                s->set_centre(Eigen::Vector3f(g["centre"][0], g["centre"][1], g["centre"][2]));
                geo = s;
                

            } else if (g["type"] == "rectangle"){

                Rectangle *r = new Rectangle();

                r->set_p1(Eigen::Vector3f(g["p1"][0], g["p1"][1], g["p1"][2]));
                r->set_p2(Eigen::Vector3f(g["p2"][0], g["p2"][1], g["p2"][2]));
                r->set_p3(Eigen::Vector3f(g["p3"][0], g["p3"][1], g["p3"][2]));
                r->set_p4(Eigen::Vector3f(g["p4"][0], g["p4"][1], g["p4"][2]));

                Eigen::Vector3f calculated_normal = (r->get_p2() - r->get_p1()).cross(r->get_p4() - r->get_p1()).normalized();
                r->set_n(calculated_normal);
                geo = r;


            } else {
                std::cout << "Geometry other than sphere or rectangle detected. Failure." << std::endl;
                std::exit(0);
            };

            geo->set_type(std::string(g["type"]));
            geo->set_ac(Eigen::Vector3f(g["ac"][0], g["ac"][1], g["ac"][2]));
            geo->set_dc(Eigen::Vector3f(g["dc"][0], g["dc"][1], g["dc"][2]));
            geo->set_sc(Eigen::Vector3f(g["sc"][0], g["sc"][1], g["sc"][2]));
            geo->set_ka(float(g["ka"]));
            geo->set_kd(float(g["kd"]));
            geo->set_ks(float(g["ks"]));
            geo->set_pc(float(g["pc"]));
            // the obligated members shared by both rec and sph

            if (g.contains("transform")) {
                // do something with the transform
            };

            this->geoms.push_back(geo);
        };

    } else {
        std::cout << "JSON file needs to have at least 1 geometry. Detected 0." << std::endl;
    }
};

void RayTracer::test() {
    // just a quick test function that returns specific values so that i can make sure things are working correctly

    for (const auto& i : this->geoms) {
        i->test();
    }

};

void RayTracer::run(){

    this->extract_data();
    this->test();
};
