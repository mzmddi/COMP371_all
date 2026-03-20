

// ---INCLUDE---
#include "Output.h"

#include <iostream>
// ---CODE---

void Output::test()
{
    std::cout << "Filename: " << this->get_output_filename() << std::endl;
    std::cout << "Width: " << this->get_width() << std::endl;
    std::cout << "Height: " << this->get_height() << std::endl;
    std::cout << "fov: " << this->get_fov() << std::endl;
    std::cout << "Centre: " << this->get_centre().transpose() << std::endl;
    std::cout << "Up: " << this->get_up().transpose() << std::endl;
    std::cout << "lookat: " << this->get_lookat().transpose() << std::endl;
    std::cout << "ai: " << this->get_ai().transpose() << std::endl;
    std::cout << "bkc" << this->get_bkc().transpose() << std::endl;
};
