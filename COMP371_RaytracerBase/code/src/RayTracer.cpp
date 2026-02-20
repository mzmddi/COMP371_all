// ---NOTES---
/*
 */

// ---INCLUDES---
#include "RayTracer.h"
#include <iostream>
#include <string>

using namespace std;

//---CODE---

RayTracer::RayTracer(const nlohmann::json &input_j) : json_(input_j) {}

void RayTracer::extract()
{

    if (json_.contains("geometry") && (json_["geometry"].size() >= 1))
    {
        // loop over all the shapes defined in the json
        for (auto i = json_["geometry"].begin(); i != json_["geometry"].end(); i++)
        {
            if ((*i)["type"] == "sphere")
            {
                shape *s = new sphere();
                s->extractInformation(*i);
                shapes_.push_back(s);
            }
            else if ((*i)["type"] == "rectangle")
            {
                shape *r = new rectangle();
                r->extractInformation(*i);
                shapes_.push_back(r);
            };
        };
    }
    else
    {
        cout << "JSON file needs to contain at least one shape in the geometry key!" << endl;
        std::exit(0);
    };

    // check if the json contains output
    if (json_.contains("output"))
    {
        output_ = new output();
        // need to change this to basic constructor
        output_->extractInformation(json_["output"][0]);
    }
    else
    {
        cout << "Did not detect output in json, so cannot proceed further." << endl;
        exit(0);
    };
};

void RayTracer::test_coding()
{
    cout << "\nSize of the shapes vector: " << shapes_.size() << "\n";
    for (int i = 0; i < shapes_.size() - 1; i++)
    {
        cout << "Shape [" << i << "]: " << shapes_.at(i)->getType() << "\n";
    };
    cout << "\noutput variable data: " << "\n";
    cout << output_->filename_ << endl;
    cout << output_->size_.at(1) << endl;
    cout << output_->lookat_ << endl;
};

void RayTracer::run()
{
    // this is the method called by the main.cpp file
    // this is the entry point of my solution

    extract();
    test_coding();
};