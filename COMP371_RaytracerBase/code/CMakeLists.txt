cmake_minimum_required(VERSION 3.8)

project(raytracer) 

#IMPORTANT COMPILING DIRECTIVES

# 1
# Enable this when you start working on your solution and you add the file RayTracer.h 
# in the src folder; Without this file the code base will not compile therefore in your 
# code this define is disabled
# Also do not forget to create the src folder under code
add_compile_options(-DSTUDENT_SOLUTION)


# 2
# This define is used by the teaching team to compile and run the official solution
# Students: for your project this define should always be commented out
# If we commit it by mistake please disable it and let us know
#add_compile_options(-DCOURSE_SOLUTION)


# When testing large scenes the debug mode will be very slow
# so switch to release
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH
    /encs # For ENCS lab computers
    /opt/local # Macports
)

# ENCS Eigen3 CMake setup
if (WIN32)
include_directories(C:/eigen-3.4.1/)# for windows you can directly hardcode the paths to your libraries in the include
else() 
# Code added by me
# cause error cause i dont have eigen and it's trying to pull from the school server
# this added code is to specify the path of eigen for my macbook m2
# the code is if statement based, hopefully this works intergrated with the entire code
if(APPLE)
set(Eigen3_DIR /opt/homebrew/share/eigen3/cmake)
else()
# added code by me ends here
set(ENV{EIGEN3_ROOT} /encs/pkg/eigen-3.3.7/root)
set(CMAKE_MODULE_PATH /encs/pkg/eigen-3.3.7/root/cmake)
endif()
# the above line is also added by me to complete the if else block

find_package(Eigen3 REQUIRED)
# include_directories(${EIGEN3_INCLUDE_DIR})
# added code below until the endif()
include_directories(${EIGEN3_INCLUDE_DIRS})
link_libraries(Eigen3::Eigen)
endif()
# If you need too manually add the paths to your Eigen library, you can add it here
# do not delete the other 

# These folders include some important header files including the header files for your own solution
#do not remove
include_directories(src/)
include_directories(external/)

#internal includes
aux_source_directory(external SOURCE)
aux_source_directory(src SOURCE)

add_executable(raytracer main.cpp ${SOURCE}) #The name of the cpp file and its path can vary

