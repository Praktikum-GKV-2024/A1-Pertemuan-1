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

    float positions[] = {
        // Vertex positions for the star
        0.0f,  0.5f,   // 0
        0.15f, 0.15f,  // 1
        0.5f,  0.15f,  // 2
        0.2f,  -0.15f, // 3
        0.3f,  -0.5f,  // 4
        0.0f,  -0.25f, // 5
        -0.3f, -0.5f,  // 6
        -0.2f, -0.15f, // 7
        -0.5f, 0.15f,  // 8
        -0.15f, 0.15f // 9
    };

    unsigned int indices[] = {
        // Indices to form the star
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 9,
        0, 9, 1
    };

    // Initialize Vertex Array Buffer
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Setup vertex buffers
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 10 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    // Setting the layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  // Index untuk layout VAO
        2,                  // Vector size of data type
        GL_FLOAT,           // Data type
        GL_FALSE,           // Normalized? Map to 0 - 255
        2 * sizeof(float),  // Gaps
        0                   // Offset
    );

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 27 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

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

        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, nullptr);


        // glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};