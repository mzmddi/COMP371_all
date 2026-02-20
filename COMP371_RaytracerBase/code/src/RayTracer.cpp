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
    cout << output_->bkc_[0] << " " << output_->bkc_[1] << " " << output_->bkc_[2] << std::endl;
};

void RayTracer::run()
{
    // this is the method called by the main.cpp file
    // this is the entry point of my solution

    extract();
    test_coding();

    Vector3f w = (output_->centre_ - output_->lookat_).normalized();
    // one of the basis vectors the w

    Vector3f u = output_->up_.cross(w).normalized();
    // the u basis vector which points to the right of the camera

    Vector3f v = w.cross(u);
    // the v basis vector which is up (very up)

    float width = (float)output_->size_[0];
    float height = (float)output_->size_[1];
    cout << "Testing new values w h fov:  " << width << " " << height << " " << output_->fov_ << std::endl;

    float theta = output_->fov_ * (EIGEN_PI / 180.0f);
    float halfHeight = tan(theta / 2.0f);
    float aspectRatio = width / height;
    float halfWidth = aspectRatio * halfHeight;

    cout << "Testing new values in order: " << theta << " " << halfHeight << " " << aspectRatio << " " << halfWidth << std::endl;

    // create the vector of vectors that will store all our pixel values
    std::vector<Vector3f> buffer(width * height);

    cout << "size of buffer: " << buffer.size() << std::endl;

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // first we need to normalise the coordinates of the pixel between -1 and 1
            float x = (2.0f * (i + 0.5f) / width) - 1.0f;
            float y = 1.0f - (2.0f * (j + 0.5f) / height);

            // now we calculate the direction of the ray coming out of this pixel x,y
            Vector3f d = (x * halfWidth * u) + (y * halfHeight * v) - w;
            d.normalize();
            // we need to bring the direction back to unit length since it is a direction vector

            Vector3f o = output_->centre_;
            // the origin of the ray taken from class output which is taken from the json file

            bool hitormiss = false;
            // false if the ray hit nothing, true if it did

            float closesthit = std::numeric_limits<float>::max();
            // we only care about the closest hit relative to the camera
        };
    };

    cout << "success" << endl;
};