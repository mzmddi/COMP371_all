

// ---INCLUDE---

#include "RayTracer.h"

#include <iostream>
#include <Eigen/Geometry>

// ---CODE---

RayTracer::RayTracer(const nlohmann::json &input_j) : json_obj(input_j) {};

void RayTracer::extract_data()
{

    if (this->json_obj.contains("geometry") && (this->json_obj["geometry"].size() >= 1))
    {

        for (const auto &g : this->json_obj["geometry"])
        {
            Geom *geo = nullptr;

            if (g["type"] == "sphere")
            {

                Sphere *s = new Sphere();

                s->set_radius(float(g["radius"]));
                s->set_centre(Eigen::Vector3f(g["centre"][0], g["centre"][1], g["centre"][2]));
                geo = s;
            }
            else if (g["type"] == "rectangle")
            {

                Rectangle *r = new Rectangle();

                r->set_p1(Eigen::Vector3f(g["p1"][0], g["p1"][1], g["p1"][2]));
                r->set_p2(Eigen::Vector3f(g["p2"][0], g["p2"][1], g["p2"][2]));
                r->set_p3(Eigen::Vector3f(g["p3"][0], g["p3"][1], g["p3"][2]));
                r->set_p4(Eigen::Vector3f(g["p4"][0], g["p4"][1], g["p4"][2]));

                Eigen::Vector3f calculated_normal = (r->get_p2() - r->get_p1()).cross(r->get_p4() - r->get_p1()).normalized();
                r->set_n(calculated_normal);
                geo = r;
            }
            else
            {
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

            if (g.contains("transform"))
            {
                // do something with the transform
            };

            this->geoms.push_back(geo);
        };
    }
    else
    {
        std::cout << "JSON file needs to have at least 1 geometry. Detected 0." << std::endl;
    };

    if (this->json_obj.contains("light") && (this->json_obj["light"].size() >= 1))
    {
        for (const auto &l : this->json_obj["light"])
        {
            if (l.contains("use"))
            {
                if (!l["use"])
                {
                    continue;
                }
            }
            Light *light = nullptr;
            // forward declare one pointer used for this light source

            if (l["type"] == "area")
            {

                AreaLight *al = new AreaLight();

                al->set_p1(Eigen::Vector3f(l["p1"][0], l["p1"][1], l["p1"][2]));
                al->set_p2(Eigen::Vector3f(l["p2"][0], l["p2"][1], l["p2"][2]));
                al->set_p3(Eigen::Vector3f(l["p3"][0], l["p3"][1], l["p3"][2]));
                al->set_p4(Eigen::Vector3f(l["p4"][0], l["p4"][1], l["p4"][2]));
                // setting all the area light corners

                light = al;
            }
            else if (l["type"] == "point")
            {
                PointLight *pl = new PointLight();

                pl->set_centre(Eigen::Vector3f(l["centre"][0], l["centre"][1], l["centre"][2]));

                light = pl;
            };

            light->set_type(std::string(l["type"]));
            light->set_id(Eigen::Vector3f(l["id"][0], l["id"][1], l["id"][2]));
            light->set_is(Eigen::Vector3f(l["is"][0], l["is"][1], l["is"][2]));

            if (l.contains("transform"))
            {
                // code that handles the transform transfer
            };

            if (l.contains("usecenter"))
            {
                light->set_usecenter(bool(l["usecenter"]));
            };
            if (l.contains("n"))
            {
                light->set_n(int(l["n"]));
            };

            this->lights.push_back(light);
        };
    }
    else
    {
        std::cout << "JSON file needs to have at least 1 light. Detected 0." << std::endl;
    };

    if (this->json_obj.contains("output") && (this->json_obj["output"].size() >= 1))
    {
        for (const auto &o : this->json_obj["output"])
        {

            Output *output = new Output();

            output->set_output_filename(std::string(o["filename"]));
            output->set_width(int(o["size"][0]));
            output->set_height(int(o["size"][1]));
            output->set_fov(float(o["fov"]));
            output->set_centre(Eigen::Vector3f(o["centre"][0], o["centre"][1], o["centre"][2]));
            output->set_up(Eigen::Vector3f(o["up"][0], o["up"][1], o["up"][2]));
            output->set_lookat(Eigen::Vector3f(o["lookat"][0], o["lookat"][1], o["lookat"][2]));
            output->set_ai(Eigen::Vector3f(o["ai"][0], o["ai"][1], o["ai"][2]));
            output->set_bkc(Eigen::Vector3f(o["bkc"][0], o["bkc"][1], o["bkc"][2]));
            // assigning all the mandatory values first

            if (o.contains("raysperpixel"))
            {
                output->set_using_rayperpixel(true);
                int len_raysperpixel = o["raysperpixel"].size();
                if (len_raysperpixel == 1)
                {
                    Eigen::VectorXf v(1);
                    v[0] = o["raysperpixel"][0].get<float>();
                    output->set_raysperpixel(v);
                }
                else if (len_raysperpixel == 2)
                {
                    Eigen::VectorXf v(2);
                    v[0] = o["raysperpixel"][0].get<float>();
                    v[1] = o["raysperpixel"][1].get<float>();
                    output->set_raysperpixel(v);
                }
                else if (len_raysperpixel == 3)
                {
                    Eigen::VectorXf v(3);
                    v[0] = o["raysperpixel"][0].get<float>();
                    v[1] = o["raysperpixel"][1].get<float>();
                    v[2] = o["raysperpixel"][2].get<float>();
                    output->set_raysperpixel(v);
                }
                else
                {
                    std::cout << "More than 3 values are given for raysperpixel, when the Max is 3. Failure." << std::endl;
                    std::exit(0);
                };

                if (o.contains("antialiasing"))
                {
                    output->set_antialiasing(bool(o["antialiasing"]));
                };
            };
            if (o.contains("twosiderender"))
            {
                output->set_twosiderender(bool(o["twosiderender"]));
            };
            if (o.contains("globalillum"))
            {
                output->set_globalillum(bool(o["globalillum"]));
            };
            if (o.contains("maxbounces"))
            {
                output->set_maxbounces(float(o["maxbounces"]));
            };
            if (o.contains("probterminate"))
            {
                output->set_probterminate(float(o["probterminate"]));
            };

            this->outputs.push_back(output);
        };
    }
    else
    {
        std::cout << "JSON file needs to have at least 1 output. Detected 0." << std::endl;
    }
};

void RayTracer::test() {
    // just a quick test function that returns specific values so that i can make sure things are working correctly

    // for (const auto &i : this->geoms)
    // {
    //     i->test();
    // };
    // for (const auto &i : this->lights)
    // {
    //     i->test();
    // };
    // for (const auto &i : this->outputs)
    // {
    //     i->test();
    // };
};

void RayTracer::run()
{

    this->extract_data();
    // this->test();

    int counter = 0;

    for (auto output : this->outputs)
    {
        // we want to loop over each output from the json file so that we render one for each.

        Eigen::Vector3f w_basis = (output->get_centre() - output->get_lookat()).normalized();
        Eigen::Vector3f u_basis = output->get_up().cross(w_basis).normalized();
        Eigen::Vector3f v_basis = w_basis.cross(u_basis).normalized();
        // the 3 basis vectors needed

        float camera_distance = 1.0f;
        // let's just assume that camera distance is 1
        // check other test json files later if there's a camera distance defined or something and adjust extract() and this variable

        Eigen::Vector3f proj_screen_center = output->get_centre() - (camera_distance * w_basis);
        // centre of the screen in viewport

        float theta = output->get_fov() * M_PI / 180.0f;
        // getting the angle from the fov

        float vp_height = 2.0f * tan((output->get_fov() * M_PI / 180.0f) / 2.0f) * camera_distance;
        float aspect_ratio = (float)output->get_width() / (float)output->get_height();
        float vp_width = aspect_ratio * vp_height;
        // get the vp width and height

        Eigen::Vector3f proj_width = u_basis * vp_width;
        Eigen::Vector3f proj_height = v_basis * vp_height;
        // now i have the projection width and height

        Eigen::Vector3f top_left = proj_screen_center - (proj_width / 2.0f) + (proj_height / 2.0f);
        // defining the top left pixel that we will start at

        Eigen::Vector3f du = proj_width / (float)output->get_width();
        Eigen::Vector3f dv = proj_height / (float)output->get_height();
        // the steps we take when we move on from pixel to pixel
        // du -> along u basis
        // dv -> along v basis

        const int x = output->get_width();
        const int y = output->get_height();
        // im gonna set the screen pixel size to a local variable so that for the loop, it doesnt call the variable every singel time

        std::cout << "w_basis: " << w_basis.transpose() << std::endl;
        std::cout << "u_basis: " << u_basis.transpose() << std::endl;
        std::cout << "v_basis: " << v_basis.transpose() << std::endl;
        std::cout << "proj_width: " << proj_width.transpose() << std::endl;
        std::cout << "proj_height: " << proj_height.transpose() << std::endl;
        std::cout << "du: " << du.transpose() << std::endl;
        std::cout << "dv: " << dv.transpose() << std::endl;
        std::cout << "top_left: " << top_left.transpose() << std::endl;

        for (int j = 0; j < y; j++)
        {
            for (int i = 0; i < x; i++)
            {
                // main loop for raytracing
                // loops over j then inside over i because
                // we want it to loop row by row which is counterintuitively looping over the height

                Eigen::Vector3f current_pix = top_left + (i + 0.5f) * du - (j + 0.5f) * dv;
                // moving from top left, so each x moves right and each y moves down one row

                // Ray *r = Ray();
                // generating a new ray;

                // r->set_o();
                // r->set_d();
                // set the origin + direction of the newly created ray

                counter++;
            };
        };

        // del(output);
        // once we are done with this output, we want to destroy the memory of the pointer
        // this is done because output was defined with new, so its on the heap, not on a stack
    }; //
    std::cout << "Counter of pixels: " << counter << std::endl;
};
