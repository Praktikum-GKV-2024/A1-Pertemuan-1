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

        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

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

    // Vertices yang di-pass ke GPU
    float positions[] = {
    // Triangle 1 (Base)
    -0.5f, -0.5f, // 0
    0.5f, -0.5f,  // 1
    0.0f,  0.5f,  // 2

    // Triangle 2 (Left Side)
    -0.6f, -0.5f, // 3
    -0.5f,  0.5f, // 4
    0.0f,  0.0f,  // 5

    // Triangle 3 (Right Side)
    0.5f, -0.5f,  // 6
    0.6f,  0.5f,  // 7
    0.0f,  0.0f,  // 8

    // Triangle 4 (Top Left)
    -0.5f, 0.6f,  // 9
    -0.2f, 0.8f,  // 10
    0.0f,  0.2f,  // 11

    // Triangle 5 (Top Right)
    0.2f, 0.8f,   // 12
    0.5f, 0.6f,   // 13
    0.0f, 0.2f    // 14
};

unsigned int indices[] = {
    0, 1, 2, // Triangle 1 (Base)
    3, 4, 5, // Triangle 2 (Left Side)
    6, 7, 8, // Triangle 3 (Right Side)
    9, 10, 11, // Triangle 4 (Top Left)
    12, 13, 14 // Triangle 5 (Top Right)
};


    // Initialize Vertex Array Buffer
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Setup vertex buffers
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 13 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    // Setting the layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, // Index untuk layout VAO
        2, // Vector size of data type
        GL_FLOAT, // Data type
        GL_FALSE, // Normalized? Map to 0 - 255
        2 * sizeof(float), // Gaps
        0                  // Offset
    );

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 26 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

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

        glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, nullptr);


        glDrawArrays(GL_TRIANGLES, 4, 16);
    }
}; 