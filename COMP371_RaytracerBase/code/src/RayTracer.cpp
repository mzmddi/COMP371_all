// ---NOTES---
/*
 */

// ---INCLUDES---
#include "RayTracer.h"
#include <iostream>
#include <string>
#include "Eigen/Dense"
#include "simpleppm.h"

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
        // output_ = new output();
        // need to change this to basic constructor
        //output_->extractInformation(json_["output"][0]);
        this->size_.push_back(json_["output"][0]["size"].at(0).get<int>());
        this->size_.push_back(json_["output"][0]["size"].at(1).get<int>());
        this->lookat_ << json_["output"][0]["lookat"].at(0).get<float>(), json_["output"][0]["lookat"].at(1).get<float>(), json_["output"][0]["lookat"].at(2).get<float>();
        this->up_ << json_["output"][0]["up"].at(0).get<float>(), json_["output"][0]["up"].at(1).get<float>(), json_["output"][0]["up"].at(2).get<float>();
        this->filename_ = json_["output"][0]["filename"];
        this->centre_ << json_["output"][0]["centre"].at(0).get<float>(), json_["output"][0]["centre"].at(1).get<float>(), json_["output"][0]["centre"].at(2).get<float>();
        this->bkc_ << json_["output"][0]["bkc"].at(0).get<float>(), json_["output"][0]["bkc"].at(1).get<float>(), json_["output"][0]["bkc"].at(2).get<float>();
        this->fov_ = json_["output"][0]["fov"];
    }
    else
    {
        cout << "Did not detect output in json, so cannot proceed further." << endl;
        exit(0);
    };
};

void RayTracer::test_coding()
{
    cout << "size of shape vector: " << this->shapes_.size() << endl;
    cout << "output filename: " << this->filename_ << endl;
    cout << "window size: " << this->size_[0] << " " << this->size_[1] << endl;
    cout << "lookat vector: "<<this->lookat_[0] << " " << this->lookat_[1] << " " << this->lookat_[2] << endl;
    cout << "background color: "<< this->bkc_[0] << " " << this->bkc_[1] << " " << this->bkc_[2] << std::endl;
};
   

void RayTracer::run()
{
    // this is the method called by the main.cpp file
    // this is the entry point of my solution

    extract();
    test_coding();
    // for testing the values

    Vector3f w = (this->centre_ - this->lookat_).normalized();
    // one of the basis vectors the w

    Vector3f u = this->up_.cross(w).normalized();
    // the u basis vector which points to the right of the camera

    Vector3f v = w.cross(u);
    // the v basis vector which is up (very up)

    float width = (float)this->size_[0];
    float height = (float)this->size_[1];

    float theta = this->fov_ * (EIGEN_PI / 180.0f);
    float halfHeight = tan(theta / 2.0f);
    float aspectRatio = width / height;
    float halfWidth = aspectRatio * halfHeight;

    // create the vector of vectors that will store all our pixel values
    std::vector<Vector3f> buffer(width * height);

    Vector3f backgroundColor = this->bkc_;
    Vector3f objectColor;

    if (backgroundColor.isZero())
    {
        objectColor = Vector3f(1.0f, 1.0f, 0.0f);
    }
    else
    {
        objectColor = Vector3f(0.0f, 0.0f, 0.0f);
    };

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

            Vector3f o = this->centre_;
            // the origin of the ray taken from class output which is taken from the json file

            bool hitormiss = false;
            // false if the ray hit nothing, true if it did

            float closesthit = std::numeric_limits<float>::max();
            // we only care about the closest hit relative to the camera

            for (auto s : shapes_)
            {
                if (s->intersect(o, d))
                {
                    hitormiss = true;
                    break;
                    // since this is the first ray tracing, im stopping here since we only need to know if it hits or not
                }
            };
            int pixelPositionIndex = j * width + i;
            if (hitormiss)
            {
                buffer[pixelPositionIndex] = objectColor;
            }
            else
            {
                buffer[pixelPositionIndex] = backgroundColor;
            };
        };
    };

    std::vector<double> flatBuffer;
    flatBuffer.reserve(width * height * 3);
    // i need to change my vector<Vector3f> buffer to a flat one with doubles only...

    for (const auto &v : buffer)
    {
        flatBuffer.push_back(static_cast<double>(v[0]));
        flatBuffer.push_back(static_cast<double>(v[1]));
        flatBuffer.push_back(static_cast<double>(v[2]));
        // since the save_ppm file needs a flat vector, i need to push back each element in the Vector3f i created
        // so the sequence in the flat buffer is just rgbrgbrgbrgb over and over again
    }

    save_ppm(this->filename_, flatBuffer, width, height);
};