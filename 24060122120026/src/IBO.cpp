#define GLM_FORCE_PURE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <common/loader.hpp>
#include <common/controls.hpp>
#include <common/shader.hpp>

#define GLCall(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__)

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}
static void GLLogCall(const char* function_name, const char* file, int line) {
    while (GLenum error = glGetError()) {
        cout << "Triggered Error Code: " << error << " at function call " << function_name << ", at " << file << ":" << line << std::endl;
    }
}

class MainScene {
public:
    GLFWwindow* window;
    GLuint vao;
    GLuint buffer;
    GLuint ibo;
    GLuint programId;

    MainScene (GLFWwindow* window) {
        this->window = window;

        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it is closer to the camera than the former one
        glDepthFunc(GL_LESS); 

        // Cull triangles which normal is not towards the camera
        // glEnable(GL_CULL_FACE);

        start();
    }

    void start() {
        programId = LoadShaders("res/shader/super_basic.vs", "res/shader/super_basic.fs");

        // vertecies yang di pass ke GPU
        float positions[] = {
             0.f, 0.f, 1.0, 1.0, 1.0,    //v0 (W)
             0.2f, 0.f, 0.0, 0.0, 1.0,   //v1 (B)
             0.f, -0.2f, 0.0, 1.0, 0.0,  //v2 (G)
             -0.2f, 0.f, 0.0, 0.0, 1.0,  //v3 (B)
             0.f, 0.2f, 0.0, 1.0, 0.0,   //v4 (G)
             0.2f, 0.2f, 0.0, 0.0, 1.0,  //v5 (B)
             0.2f, -0.2f, 0.0, 1.0, 0.0,  //v6 (G)
             -0.2f, -0.2f, 0.0, 0.0, 1.0,  //v7 (B)
             -0.2f, 0.2f, 0.0, 1.0, 0.0,  //v8 (G)
             0.4f, 0.f, 1.0, 1.0, 1.0,   //v9 (W)
             0.f, -0.4f, 1.0, 1.0, 1.0,  //v10 (W)
             -0.4f, 0.f, 1.0, 1.0, 1.0,  //v11 (W)
             0.f, 0.4f, 1.0, 1.0, 1.0,   //v12 (W)
             0.4f, 0.4f, 1.0, 0.0, 0.0,  //v13 (R)
             0.4f, -0.4f, 1.0, 0.0, 0.0,  //v14 (R)
             -0.4f, -0.4f, 1.0, 0.0, 0.0,  //v15 (R)
             -0.4f, 0.4f, 1.0, 0.0, 0.0,  //v16 (R)
        };

        unsigned int indices[] = {
            0, 1, 2, //0 (belah)
            0, 2, 3,
            0, 3, 4,
            0, 4, 1, //4 (ketupat)
            4, 5, 1, //5 (ko)
            1, 6, 2,
            2, 7, 3,
            3, 8, 4, //8 (tak)
            5, 9, 6, //9 (belah)
            6, 10, 7,
            7, 11, 8,
            8, 12, 5, //12 (ketupat)
            12, 13, 5, //13 (luaran)
            5, 13, 9,
            9, 14, 6,
            6, 14, 10, 
            10, 15, 7, 
            7, 15, 11,
            11, 16, 8,
            8, 16, 12 //16
        };

        // Initialize Vertex Array Buffer
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // setup vertex buffers
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 5 * 17 * sizeof(float), positions, GL_STATIC_DRAW);

        // setting the layout
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0, // index untuk layout VAO
            2, // vector size of data type
            GL_FLOAT, // data type
            GL_FALSE, // normalized? map to 0 - 255
            5 * sizeof(float), // gaps
            0                  // offset
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, // index untuk layout VAO
            3, // vector size of data type
            GL_FLOAT, // data type
            GL_FALSE, // normalized? map to 0 - 255
            5 * sizeof(float), // gaps
            (void *)(2 * sizeof(float)) // offset
        );

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 20 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }

    void update() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /* do every frame here*/
        glUseProgram(programId);

        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glDrawElements(GL_TRIANGLES, 20 * 3, GL_UNSIGNED_INT, nullptr);


        // glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};