// ---NOTES---

// ---INCLUDE---
#include "shapes.h";

using namespace std;

// ---CODE----

// Sphere methods

sphere::sphere(string type, Vector3f center, float radius) : type_(type), center_(center), radius_(radius) {};
sphere::getType() const override{return type_};
sphere::extractInformation(const nlohmann::json &j) override
{
    if (j.contains("type") && j.contains("radius") && j.contains("center") && j.contains("ka") && j.contains("kd") && j.contains("ks") && j.contains("pc") && j.contains("ac") && j.contains("dc") && j.contains("sc"))
    {
        this->type_ = "sphere";
        this->center_ << j["center"][0].get<float>(), j["center"][1].get<float>(), j["center"][2].get<float>();
        this->radius_ = j["radius"].get<float>();
        this->ka_ = j["ka"].get<float>();
        this->kd_ = j["kd"].get<float>();
        this->ks_ = j["ks"].get<float>();
        this->pc_ = j["pc"].get<float>();
        this->ac_ << j["ac"][0] << j["ac"][1] << j["ac"][2];
        this->dc_ << j["dc"][0] << j["dc"][1] << j["dc"][2];
        this->sc_ << j["sc"][0] << j["sc"][1] << j["sc"][2];

        if (j.contains("transform"))
        {
            this->transform_ << j["transform"][0], j["transform"][1], j["transform"][2], j["transform"][3],
                j["transform"][4], j["transform"][5], j["transform"][6], j["transform"][7],
                j["transform"][8], j["transform"][9], j["transform"][10], j["transform"][11],
                j["transform"][12], j["transform"][13], j["transform"][14], j["transform"][15];
        }
    }
    else
    {
        cout << "Sphere is missing some mandatory values." << endl;
        exit(0)
    }
};
;

// Rectangle methods
rectangle::rectangle() {};
rectangle::getType() const override{return type_};
rectangle::extractInformation(const nlohmann::json &j) override
{
    if (j.contains("type") && j.contains("p1") && j.contains("p2") && j.contains("p3") && j.contains("p4") && j.contains("ka") && j.contains("kd") && j.contains("ks") && j.contains("pc") && j.contains("ac") && j.contains("dc") && j.contains("sc"))
    {
        this->type_ = "rectangle";
        this->p1_ << j["p1"][0].get<float>(), j["p1"][1].get<float>(), j["p1"][2].get<float>();
        this->p2_ << j["p2"][0].get<float>(), j["p2"][1].get<float>(), j["p2"][2].get<float>();
        this->p3_ << j["p3"][0].get<float>(), j["p3"][1].get<float>(), j["p3"][2].get<float>();
        this->p4_ << j["p4"][0].get<float>(), j["p4"][1].get<float>(), j["p4"][2].get<float>();
        this->ka_ = j["ka"].get<float>();
        this->kd_ = j["kd"].get<float>();
        this->ks_ = j["ks"].get<float>();
        this->pc_ = j["pc"].get<float>();
        this->ac_ << j["ac"][0] << j["ac"][1] << j["ac"][2];
        this->dc_ << j["dc"][0] << j["dc"][1] << j["dc"][2];
        this->sc_ << j["sc"][0] << j["sc"][1] << j["sc"][2];

        if (j.contains("transform"))
        {
            this->transform_ << j["transform"][0], j["transform"][1], j["transform"][2], j["transform"][3],
                j["transform"][4], j["transform"][5], j["transform"][6], j["transform"][7],
                j["transform"][8], j["transform"][9], j["transform"][10], j["transform"][11],
                j["transform"][12], j["transform"][13], j["transform"][14], j["transform"][15];
        }
    }
    else
    {
        cout << "Rectangle is missing some mandatory values." << endl;
        exit(0)
    }
};

