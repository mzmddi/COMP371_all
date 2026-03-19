#ifndef OUTPUT_H
#define OUTPUT_H

// ---INCLUDE---
#include <Eigen/Core>
#include <iostream>

// ---CODE---

class Output
{

    std::string output_filename;
    int width;
    int height;
    float fov;
    Eigen::Vector3f centre;
    Eigen::Vector3f up;
    Eigen::Vector3f lookat;
    Eigen::Vector3f ai;
    Eigen::Vector3f bkc;
    // all the mandatory members from the output

    bool using_rayperpixel;
    Eigen::VectorXf raysperpixel;
    // be carefull, this is optional but theres no default values
    // using the bool using_rayperpixel to check if rayperpixel is used or not

    bool globalillum = false;
    bool antialiasing;
    // be carefull, this is optional, but no default values
    // linked to if rayperpixel is defined or not
    // use or not antialiasing. If raysperpixel is specified, use
    // it for antialiasing. If raysperpixel is not specified,
    // make your own decision on how many rays to send

    bool twosiderender;
    // When true you should assume that the light bounces
    // the same way of it touches the front or back of the
    // object. If no value is specified, the default value is
    // true.

    int maxbounces = 0;
    // setting the default to 0
    // Maximum number of times the ray can bounce. A
    // value of 0 would reduce this to a ray tracer (i.e. a
    // value of 0 would require only a ray to the light from
    // the first intersection point.

    float probterminate;
    // optional but no  default value

public:
    Output() {};

    std::string get_output_filename() const { return this->output_filename; };
    int get_width() const { return this->width; };
    int get_height() const { return this->height; };
    float get_fov() const { return this->fov; };
    Eigen::Vector3f get_centre() const { return this->centre; };
    Eigen::Vector3f get_up() const { return this->up; };
    Eigen::Vector3f get_lookat() const { return this->lookat; };
    Eigen::Vector3f get_ai() const { return this->ai; };
    Eigen::Vector3f get_bkc() const { return this->bkc; };
    bool get_using_rayperpixel() const { return this->using_rayperpixel; };
    Eigen::VectorXf get_raysperpixel() const { return this->raysperpixel; };
    bool get_globalillum() const { return this->globalillum; };
    bool get_antialiasing() const { return this->antialiasing; };
    bool get_twosiderender() const { return this->twosiderender; };
    int get_maxbounces() const { return this->maxbounces; };
    float get_probterminate() const { return this->probterminate; };
    // all the getters for all the output variables

    void set_output_filename(std::string s) { this->output_filename = s; };
    void set_width(int s) { this->width = s; };
    void set_height(int s) { this->height = s; };
    void set_fov(float s) { this->fov = s; };
    void set_centre(Eigen::Vector3f s) { this->centre = s; };
    void set_up(Eigen::Vector3f s) { this->up = s; };
    void set_lookat(Eigen::Vector3f s) { this->lookat = s; };
    void set_ai(Eigen::Vector3f s) { this->ai = s; };
    void set_bkc(Eigen::Vector3f s) { this->bkc = s; };
    void set_using_rayperpixel(bool s) { this->using_rayperpixel = s; };
    void set_raysperpixel(Eigen::VectorXf s) { this->raysperpixel = s; };
    void set_globalillum(bool s) { this->globalillum = s; };
    void set_antialiasing(bool s) { this->antialiasing = s; };
    void set_twosiderender(bool s) { this->twosiderender = s; };
    void set_maxbounces(int s) { this->maxbounces = s; };
    void set_probterminate(float s) { this->probterminate = s; };
    // all the setters for every single class attribute
};

#endif