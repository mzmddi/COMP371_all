// ---NOTES---

// ---INCLUDE---
#include "A1solution.h"

// opengl includes below
// #include <glad/glad.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// c++ includes below
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// ---CODE---

void A1solution::keyPress(GLFWwindow *w)
{

    if (glfwGetKey(w, GLFW_KEY_E) == GLFW_PRESS)
    {
        // this is just a test press key
        glfwSetWindowShouldClose(w, true);
    };

    if (glfwGetKey(w, GLFW_KEY_R) == GLFW_PRESS)
    {
        // this is just a test press key
        this->color = {1.0f, 0.0f, 0.0f, 1.0f};
    };

    if (glfwGetKey(w, GLFW_KEY_B) == GLFW_PRESS)
    {
        // this is just a test press key
        this->color = {0.0f, 0.0f, 1.0f, 1.0f};
    };

    if (glfwGetKey(w, GLFW_KEY_P) == GLFW_PRESS)
    {
        // this is just a test press key
        this->color = {1.0f, 0.75f, 0.8f, 1.0f};
    };

    if (glfwGetKey(w, GLFW_KEY_G) == GLFW_PRESS)
    {
        // this is just a test press key
        this->color = {0.0f, 1.0f, 0.0f, 1.0f};
    };

    if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
    {
        // when s is pressed -> toggle rendering modes
        this->mode = (this->mode + 1) % 4;
    };

    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
    {
        // when w is pressed -> toggle between regular rendering and wireframe mode
        this->w_mode = (this->w_mode + 1) % 2;
    };
};

void A1solution::processInputFile(std::string &s)
{
    // part where i will extract the information of the file and put them in memory

    std::ifstream t(s);
    // using std::stringstream so that i can read each seperated-by-space string

    if (!t)
    {
        std::cout << "File " << s << " does not exist! Please verify spelling and try again." << std::endl;
        exit(0);
    };

    if (!t.is_open())
    {
        std::cout << "File " << s << " was found, but cannot open successfully for some reason." << std::endl;
    };

    std::string line;
    // word will hold the value of the stream

    int count = 0;
    // count is used to keep track of which line it is processing currently since the data is structured consistently

    int N;
    // number of vertices defined in the input text file

    int M;
    // number of triangles defined in the input file

    while (std::getline(t, line))
    {
        // this while loop is the main loop thats going to extract the data from file.

        if (count >= 0 && count <= 3)
        {
            // lines 0-3 (16 numbers over 4 lines) are the modelview matrix

            int row = count % 4;

            sscanf(line.c_str(), "%f %f %f %f", &this->modelView[row][0], &this->modelView[row][1], &this->modelView[row][2], &this->modelView[row][3]);
        }
        else if (count >= 4 && count <= 7)
        {
            // lines 4-7 (16 numbers over 4 lines) are the projection matrix

            int row = count % 4;

            sscanf(line.c_str(), "%f %f %f %f", &this->projectionView[row][0], &this->projectionView[row][1], &this->projectionView[row][2], &this->projectionView[row][3]);
        }
        else if (count == 8)
        {

            std::sscanf(line.c_str(), "%i %i", &this->size[0], &this->size[1]);
            // .c_str() outputs a pointer to the first char of the string.
            //      this is for string object to mimick how pure c char* [] works
            // since sscanf requires a c style pointer to the first char of the string, we need to do .c_str()
        }
        else if (count >= 9)
        {
            if (count == 9)
            {
                sscanf(line.c_str(), "%i", &N);
                // getting number of vertices

                this->totalVertex = N;
            }
            else if (count > 9 && count <= (9 + N))
            {
                // getting the vertices

                float f1, f2, f3;

                sscanf(line.c_str(), "%f %f %f", &f1, &f2, &f3);

                this->v.push_back(f1);
                this->v.push_back(f2);
                this->v.push_back(f3);
                // 1d vector -> x1, y1, z1, x2, y2, z2, ..., xN, yN, zN
            }
            else if (count == (9 + N + 1))
            {
                // extracting total num of triangles

                sscanf(line.c_str(), "%i", &M);

                this->totalTriangle = M;
            }
            else if (count > (9 + N + 1) && count <= (9 + N + 1 + M))
            {
                // extracting lines of the triangle

                int t1, t2, t3;

                sscanf(line.c_str(), "%i %i %i", &t1, &t2, &t3);

                this->t.push_back(t1);
                this->t.push_back(t2);
                this->t.push_back(t3);
            };
        };
        count++;
    };
    t.close();
};

void A1solution::createPhongShaderProgram()
{
    const char *vertexShaderPHONG = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aNormal;

        out vec3 FragPos;
        out vec3 Normal;

        uniform mat4 modelView;
        uniform mat4 projection;

        void main() {
            FragPos = vec3(modelView * vec4(aPos, 1.0));
            Normal = mat3(transpose(inverse(modelView))) * aNormal; 
            gl_Position = projection * vec4(FragPos, 1.0);
        }
    )glsl";
    // vertex shader for PHONG

    const char *fragmentShaderPHONG = R"glsl(
        #version 330 core
        out vec4 FragColor;

        in vec3 FragPos;
        in vec3 Normal;

        void main() {
            vec3 ambient = vec3(0.1, 0.05, 0.05);

            vec3 norm = normalize(Normal);

            vec3 lightDir = normalize(-FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * vec3(1.0, 0.5, 0.5);
            vec3 viewDir = normalize(-FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);

            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 5.0);
            vec3 specular = spec * vec3(0.3, 0.3, 0.3);
            vec3 result = ambient + diffuse + specular;

            FragColor = vec4(result, 1.0);
        }
    )glsl";
    // fragment shader for PHONG

    GLuint phongVS = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(phongVS, 1, &vertexShaderPHONG, NULL);
    glCompileShader(phongVS);
    // compiling the gsls code for phong vertex shader

    GLuint phongFS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(phongFS, 1, &fragmentShaderPHONG, NULL);
    glCompileShader(phongFS);
    // compiling the gsls code for phong fragment shader

    this->phongShaderProgram = glCreateProgram();
    glAttachShader(this->phongShaderProgram, phongVS);
    glAttachShader(this->phongShaderProgram, phongFS);
    glLinkProgram(this->phongShaderProgram);
    // linking the phong vertex + fragment shaders

    GLint success;
    char infoLog[512];

    glGetShaderiv(phongVS, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(phongVS, 512, NULL, infoLog);
        std::cout << "ERROR!! SHADER VERTEX COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    };

    glGetProgramiv(this->phongShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->phongShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR!! SHADER PROGRAM LINKING_FAILED\n"
                  << infoLog << std::endl;
    };

    glDeleteShader(phongVS);
    glDeleteShader(phongFS);
    // removing the shader objects created since we do not need them anymore
};
void A1solution::createFlatShaderProgram() {};
void A1solution::createCircleShaderProgram() {};
void A1solution::createVoronoiShaderProgram() {};

void A1solution::run(std::string s)
{
    std::cout << "Inside A1solution::run()" << std::endl;

    this->processInputFile(s);
    // all the data from the file is extracted here

    // this->test_class();

    glfwInit();

    GLFWwindow *w = glfwCreateWindow(this->size[0], this->size[1], "testing", NULL, NULL);

    if (w == NULL)
    {
        std::cout << "failed to create the window." << std::endl;
        glfwTerminate();
        return;
    };

    glfwMakeContextCurrent(w);

    glewExperimental = GL_TRUE;
    glewInit();

    std::vector<float> normals(this->v.size(), 0.0f);
    // create a vector of size of the vertex vector and initialize all the elements to 0 so we can start calculating the nromals

    // calculating all the normals of triangles
    for (int i = 0; i < this->t.size(); i += 3)
    // looping through all the triangles to get the normal for all triangles
    {
        int i1 = this->t[i];
        int i2 = this->t[i + 1];
        int i3 = this->t[i + 2];
        // getting the vertices making this specific triangle

        float v1[3] = {this->v[i1 * 3], this->v[i1 * 3 + 1], this->v[i1 * 3 + 2]};
        float v2[3] = {this->v[i2 * 3], this->v[i2 * 3 + 1], this->v[i2 * 3 + 2]};
        float v3[3] = {this->v[i3 * 3], this->v[i3 * 3 + 1], this->v[i3 * 3 + 2]};
        // from the vertices (basically the index) we got i1 i2 i3, find it in the vertex vector and extract the x y z
        // since the vector is basically x y z with the index and offset

        float e1[3] = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
        float e2[3] = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};
        // we calculate 2 edges of the triangle in question, since we only need 2 edges to calculate the normal

        float nx = e1[1] * e2[2] - e1[2] * e2[1];
        float ny = e1[2] * e2[0] - e1[0] * e2[2];
        float nz = e1[0] * e2[1] - e1[1] * e2[0];
        // doing the cross product to find the normal vectors per axis
        //    x     y     z
        //  e1[0] e1[1] e1[2]
        //  e2[0] e2[1] e2[2]
        // cross product => determinant of the vector above
        // x <= e1[1] * e2[2] - e2[1] * e1[2]
        // y <= e1[2] * e2[0] - e1[0] * e2[2]
        // z <= e1[0] * e2[1] - e1[1] * e2[0]

        normals[i1 * 3] += nx;
        normals[i1 * 3 + 1] += ny;
        normals[i1 * 3 + 2] += nz;

        normals[i2 * 3] += nx;
        normals[i2 * 3 + 1] += ny;
        normals[i2 * 3 + 2] += nz;

        normals[i3 * 3] += nx;
        normals[i3 * 3 + 1] += ny;
        normals[i3 * 3 + 2] += nz;
        // for each of the vertices of the triangle (i1 i2 i3) we add up the normal we calculated for each axis
    };

    // normalizing the normals so its all unit length 1
    for (int i = 0; i < normals.size(); i += 3)
    {
        float x = normals[i];
        float y = normals[i + 1];
        float z = normals[i + 2];
        // get the xyz of the vertex (using i and offset it by 3 every increment since this->v is a flat vector)

        float denominator = sqrt((x * x) + (y * y) + (z * z));
        if (denominator > 0.0f)
        // making sure we dont do any division by 0 to not crash the universe
        {
            normals[i] = x / denominator;
            normals[i + 1] = y / denominator;
            normals[i + 2] = z / denominator;
            // reassigning the normals but now it is normalised
        };
    };

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    // vao -> vertex array object

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->v.size() * sizeof(float), this->v.data(), GL_STATIC_DRAW);
    // vbo -> vertex coordinates

    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->t.size() * sizeof(int), this->t.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Setting the format of the way the data is handled inside the vbo and ebo
    // EBO -> triangle vertices

    glGenBuffers(1, &this->normalVbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->normalVbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    // uploading the normals data to the vbo to pass it to gl

    this->createPhongShaderProgram();

    this->currentProgram = this->phongShaderProgram;
    // for now to test it out, it is set to phong one hard coded

    glEnable(GL_DEPTH_TEST);
    // enabling depth

    while (!glfwWindowShouldClose(w))
    {
        this->keyPress(w);

        glViewport(0, 0, this->size[0], this->size[1]);

        glClearColor(this->color[0], this->color[1], this->color[2], this->color[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(this->currentProgram);
        // telling gl to use the shader program i compiled outside of the render loop
        // have something like GLuint currentprogram = one of the shaders and have a switch case with the mode being the matvhing case to the specific program being == to current program

        GLint mvLoc = glGetUniformLocation(this->currentProgram, "modelView");
        GLint pLoc = glGetUniformLocation(this->currentProgram, "projection");
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &this->modelView[0][0]);
        glUniformMatrix4fv(pLoc, 1, GL_FALSE, &this->projectionView[0][0]);
        // passing the worldview and projection view matrices to gl

        glBindVertexArray(this->vao);
        glDrawElements(GL_TRIANGLES, this->t.size(), GL_UNSIGNED_INT, 0);
        // drawing the triangles with gl

        glfwSwapBuffers(w);
        glfwPollEvents();
    };

    glfwTerminate();
    return;
};

void A1solution::test_class()
{

    std::cout << " " << std::endl;
    std::cout << "Printing all vertices from class attribute" << std::endl;
    int count_0 = 0;
    for (int i = 0; i < this->v.size(); i += 3)
    {
        std::cout << "Vertex [" << count_0 << "] => " << this->v[i] << " " << this->v[i + 1] << " " << this->v[i + 2] << std::endl;
        count_0++;
    };
    std::cout << " " << std::endl;

    std::cout << "Printing all triangles from class attribute, size of triangle vector: " << this->t.size() << std::endl;
    int count_1 = 0;
    for (int j = 0; j < this->t.size(); j += 3)
    {
        std::cout << "Triangle [" << count_1 << "] => " << this->t[j] << " " << this->t[j + 1] << " " << this->t[j + 2] << std::endl;
        count_1++;
    };
    std::cout << " " << std::endl;

    std::cout << "Total number of vertices => " << this->totalVertex << std::endl;
    std::cout << "Total number of triangles => " << this->totalTriangle << std::endl;
    std::cout << " " << std::endl;

    std::cout << "Printing this->size => (" << this->size[0] << ", " << this->size[1] << ")" << std::endl;
    std::cout << " " << std::endl;

    std::cout << "Printing model view matrix from class attribute" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << this->modelView[i][j] << " ";
        };

        std::cout << " " << std::endl;
    };
    std::cout << " " << std::endl;

    std::cout << "Printing projection view from class attribute" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << this->projectionView[i][j] << " ";
        };

        std::cout << " " << std::endl;
    };
    std::cout << " " << std::endl;
};
