

// ---INCLUDE---

#include "RayTracer.h"

#include <iostream>

// ---CODE---

RayTracer::RayTracer(const nlohmann::json &input_j) : json_obj(input_j) {};

void RayTracer::extract_data(){

    if (this->json_obj.contains("geometry") && (this->json_obj.size() >= 1)) {

        for (const auto& g : this->json_obj["geometry"]) {
            if (g["type"] == "sphere") {

                Sphere *s = new Sphere();

                s->set_radius(float(g["radius"]));
                s->set_centre(Eigen::Vector3f(g["centre"][0], g["centre"][1], g["centre"][2]));
                s->set_type(std::string(g["type"]));

                this->geoms.push_back(s);
            }
        }

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
