// ---NOTES---

// ---INCLUDE---
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ---CODE---

class A1solution
{
    int mode = 0;
    // using integers to set the state of the mode
    // 0 => Phong shader
    // 1 => flat shader
    // 2 => circle shader
    // 3 => voronoi shader

    int w_mode = 0;
    // using integers to set the stae of if it;s regular shading or wireframe mode
    // 0 => regular shading
    // 1 => wireframe mode

    float modelView[4][4];
    // the matrix for the model view matrix (4,4)
    // values are from the input file

    float projectionView[4][4];
    // the matrix for the projection view matrix (4,4)
    // values are from the input file

    int size[2];
    // size of the window
    // value from the file

    int totalVertex;
    int totalTriangle;

    std::vector<float> v;
    // all the vertices
    // values from the input file
    // vector of vector of floats
    // v is the vector of the vertex corpus
    // v[i] is the vertex of index i, i is the same index in the triangle corpus defining the triangles from vertices

    std::vector<int> t;
    // all the triangles
    // t[i] -> i is the triangle index, the output of this is a vector of ints, each int representing the index of the vertex in v

    std::vector<float> color = {1.0f, 1.0f, 1.0f, 1.0f};
    // for testing - to be removed after

    GLuint vao, vbo, ebo, normalVbo;
    // the specific data structures needed for opengl for my gpu to use

    GLuint phongShaderProgram;
    GLuint flatShaderProgram;
    GLuint circleShaderProgram;
    GLuint voronoiShaderProgram;
    // the 4 types of shader programs i need, these will be toggled
    GLuint currentProgram;
    // this is the current shader program being used

public:
    A1solution() {};
    void run(std::string s);

private:
    void keyPress(GLFWwindow *w);
    void processInputFile(std::string &s);
    void test_class();

    void createPhongShaderProgram();
    void createFlatShaderProgram();
    void createCircleShaderProgram();
    void createVoronoiShaderProgram();
    // the 4 types of shader program i need to create to use in my render loop
};