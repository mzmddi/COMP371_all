// ---NOTES---

// ---INCLUDE---
#include "commons.h"
#include <iostream>

// ---CODE---

// float output::getFov() { return fov_; };
// Vector3f output::getLookat() { return lookat_; };
// Vector3f output::getUp() { return up_; };
// void output::extractInformation(const nlohmann::json &j)
// {
//     this->size_.push_back(j["size"].at(0).get<int>());
//     this->size_.push_back(j["size"].at(1).get<int>());
//     this->lookat_ << j["lookat"].at(0).get<float>(), j["lookat"].at(1).get<float>(), j["lookat"].at(2).get<float>();
//     this->up_ << j["up"].at(0).get<float>(), j["up"].at(1).get<float>(), j["up"].at(2).get<float>();
//     this->filename_ = j["filename"];
//     this->centre_ << j["centre"].at(0).get<float>(), j["centre"].at(1).get<float>(), j["centre"].at(2).get<float>();
//     this->bkc_ << j["bkc"].at(0).get<float>(), j["bkc"].at(1).get<float>(), j["bkc"].at(2).get<float>();
//     this->fov_ = j["fov"];
// };