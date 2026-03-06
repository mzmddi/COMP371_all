// ---NOTES---
/*
 */

// ---INCLUDES---
#include "RayTracer.h"
#include <iostream>
#include <string>
#include "Eigen/Dense"
#include "simpleppm.h"
#include "HitRecord.h"
#include "Ray.h"

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
    cout << "3 basis vectors:" << endl;
    cout << "w: " << this->w_basis.transpose() << " " << "u: " << this->u_basis.transpose() << " " << "v: " << this->v_basis.transpose() << endl;
    cout << "lookat: " << this->lookat_.transpose() << " up: " << this->up_.transpose() << endl; 

};

void RayTracer::create_basis_vectors() {
    // this method abstracts the creation of the 3 basis vectors w,u,v

    this->w_basis = (this->centre_ - this->lookat_).normalized();
    this->u_basis = (this->up_.cross(this->w_basis)).normalized();
    this->v_basis = (this->w_basis.cross(this->u_basis)).normalized();  
};

void RayTracer::create_camera_data() {

    this->view_plane_height = 2 * tan(this->fov_ / 180 * M_PI / 2) * this->lookat_.norm();
    this->view_plane_width = view_plane_height * this->size_[0] / this->size_[1];
    // creating the view plane height and width from the fov and aspect ratio
    // view plane is the "rectangle" from which the pixels are going to be drawn from, but using the measurements of the image world

    this->u_pixel_step = Vector3f(this->view_plane_width, 0, 0);
    this->v_pixel_step = Vector3f(0, -this->view_plane_height, 0); 
    // the entire width and height of the plane world in one vector

    this->du_pixel_steps = this->u_pixel_step / this->size_[0];
    this->dv_pixel_steps = this->v_pixel_step / this->size_[1];
    // now dv and du are the image world sizes for one plane view world pixel

    this->view_plane_start = this->centre_ + this->lookat_ - this->u_pixel_step/2.0 - this->v_pixel_step/2.0;
    // view plane start is top left of the view plane
    this->pixel_start = this->view_plane_start + (this->du_pixel_steps + this->dv_pixel_steps)/2.0;
    // the rays should come from the center of the pixel, so i need to offset the view plane start coordinates by half the size of a single pixel

};  

Ray RayTracer::create_ray(int i, int j){
    Vector3f o = this->centre_;
    Vector3f d = this->view_plane_start + j*this->du_pixel_steps + i*this->dv_pixel_steps - this->centre_;
    return Ray(o, d);
}
void RayTracer::run()
{
    // this is the method called by the main.cpp file
    // this is the entry point of my solution

    extract();

    create_basis_vectors();

    create_camera_data();
    
    HitRecord hr(this->size_[0], this->size_[1]);

    // main loop of shooting rays
    // int total_rays = 0;
    // int total_num_of_loops = 0;
    for (int i = 0; i < this->size_[1]; i++){
        // row i
        for (int j = 0; j < this->size_[0]; j++) {
            // column j

            Ray r = create_ray(i, j); 
            // step number 1 from the manual --> ray generation
            // total_rays++;
            // int counter_shapes = 1;
            for (auto s = this->shapes_.begin(); s != this->shapes_.end(); s++ ){
                // cout << "\rDoing row : " << setfill('0') << setw(3) << j << " Total num of rays generated: " << setfill('0') << setw(10) << total_rays << flush;
                // total_num_of_loops++;

                float t = (*s)->intersect(r);
                // need to go in the shapes class and do the intersection method

                hr.new_hit(i, j, t);



                // if t is a real value, create call method HitRecord::new_hit
                // pass all the relevent information to that method
                // that method should first check if at pixel j,i there's a hit, if there is, then compare the new t to the previous t already there -> keep the one thats the smallest

                

            };

        };
    };
    // cout << endl;
    // cout << "total num of loops: " << total_num_of_loops << endl;

    // ONCE loop is done, send the data from the HitRecord to the saveppm thing


    // float width = (float)this->size_[0];
    // float height = (float)this->size_[1];

    // float theta = this->fov_ * (EIGEN_PI / 180.0f);
    // float halfHeight = tan(theta / 2.0f);
    // float aspectRatio = width / height;
    // float halfWidth = aspectRatio * halfHeight;

    // // create the vector of vectors that will store all our pixel values
    // std::vector<Vector3f> buffer(width * height);

    // Vector3f backgroundColor = this->bkc_;
    // Vector3f objectColor;

    // if (backgroundColor.isZero())
    // {
    //     objectColor = Vector3f(1.0f, 1.0f, 0.0f);
    // }
    // else
    // {
    //     objectColor = Vector3f(0.0f, 0.0f, 0.0f);
    // };

    // for (int j = 0; j < height; j++)
    // {
    //     for (int i = 0; i < width; i++)
    //     {
    //         // first we need to normalise the coordinates of the pixel between -1 and 1
    //         float x = (2.0f * (i + 0.5f) / width) - 1.0f;
    //         float y = 1.0f - (2.0f * (j + 0.5f) / height);

    //         // now we calculate the direction of the ray coming out of this pixel x,y
    //         Vector3f d = (x * halfWidth * u) + (y * halfHeight * v) - w;
    //         d.normalize();
    //         // we need to bring the direction back to unit length since it is a direction vector

    //         Vector3f o = this->centre_;
    //         // the origin of the ray taken from class output which is taken from the json file

    //         bool hitormiss = false;
    //         // false if the ray hit nothing, true if it did

    //         float closesthit = std::numeric_limits<float>::max();
    //         // we only care about the closest hit relative to the camera

    //         for (auto s : shapes_)
    //         {
    //             if (s->intersect(o, d))
    //             {
    //                 hitormiss = true;
    //                 break;
    //                 // since this is the first ray tracing, im stopping here since we only need to know if it hits or not
    //             }
    //         };
    //         int pixelPositionIndex = j * width + i;
    //         if (hitormiss)
    //         {
    //             buffer[pixelPositionIndex] = objectColor;
    //         }
    //         else
    //         {
    //             buffer[pixelPositionIndex] = backgroundColor;
    //         };
    //     };
    // };

    // std::vector<double> flatBuffer;
    // flatBuffer.reserve(width * height * 3);
    // // i need to change my vector<Vector3f> buffer to a flat one with doubles only...

    // for (const auto &v : buffer)
    // {
    //     flatBuffer.push_back(static_cast<double>(v[0]));
    //     flatBuffer.push_back(static_cast<double>(v[1]));
    //     flatBuffer.push_back(static_cast<double>(v[2]));
    //     // since the save_ppm file needs a flat vector, i need to push back each element in the Vector3f i created
    //     // so the sequence in the flat buffer is just rgbrgbrgbrgb over and over again
    // }

    // vector<double> flatBuffer;
    // flatBuffer.reserve(this->size_[0] * this->size_[1] * 3);

    // for (int i = 0; i < this->size_[0]*this->size_[1]; i++){
    //     if (i % 2 == 0) {
    //         flatBuffer.push_back(0.5d);
    //         flatBuffer.push_back(0.0d);
    //         flatBuffer.push_back(0.5d);
    //     }
    //     else {
    //         flatBuffer.push_back(1.0d);
    //         flatBuffer.push_back(1.0d);
    //         flatBuffer.push_back(1.0d);
    //     };
    // };

    // save_ppm(this->filename_, flatBuffer, this->size_[0], this->size_[1]);
};