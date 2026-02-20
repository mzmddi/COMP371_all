// ---NOTES---

// ---INCLUDE---
#include "commons.h"
#include <iostream>

// ---CODE---

// ray::ray() {}
// constructor implementation for ray

// Vector3f ray::getStart() { return start_; };
// Vector3f ray::getDirection() { return direction_; };
// // getter implementation for ray

float output::getFov() { return fov_; };
Vector3f output::getLookat() { return lookat_; };
Vector3f output::getUp() { return up_; };
void output::extractInformation(const nlohmann::json &j)
{
    if (j.is_array())
    {
        std::cout << "it's an array" << std::endl;
    }
    else if (j.is_object())
    {
        std::cout << "it's an object" << std::endl;
    };
    this->size_.push_back(j["size"].at(0).get<int>());
    this->size_.push_back(j["size"].at(1).get<int>());
    this->lookat_ << j["lookat"].at(0).get<float>(), j["lookat"].at(1).get<float>(), j["lookat"].at(2).get<float>();
    this->up_ << j["up"].at(0).get<float>(), j["up"].at(1).get<float>(), j["up"].at(2).get<float>();
    this->filename_ = j["filename"];
    this->centre_ << j["centre"].at(0).get<float>(), j["centre"].at(1).get<float>(), j["centre"].at(2).get<float>();
    this->bkc_ << j["bkc"].at(0).get<float>(), j["bkc"].at(1).get<float>(), j["bkc"].at(2).get<float>();
    this->fov_ = j["fov"];
};

/*
      "filename": "cornell_box_al.ppm",
      "size": [500, 500],
      "lookat": [0, 0, -1],
      "up": [0, 1, 0],
      "fov": 40,
      "centre": [278, 273, 800],
      "ai": [1, 1, 1],
      "bkc": [0.5, 0.5, 0.5],

      "globalillum": false,
      "raysperpixel": [10, 10],
      "maxbounces": 3,
      "probterminate": 0.333
*/