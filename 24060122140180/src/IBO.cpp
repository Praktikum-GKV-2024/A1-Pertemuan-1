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

    #include <GLFW/glfw3.h>

void start() {
    programId = LoadShaders("res/shader/super_basic.vs", "res/shader/super_basic.fs");

    // Verteks untuk empat segitiga bersebelahan dengan ukuran yang sama
    float positions[] = {
        // Segitiga pertama (segitiga kiri atas)
        -0.5f,  0.25f, // atas kiri
        -1.0f, -0.25f, // kiri bawah
         0.0f, -0.25f, // kanan bawah
        // Segitiga kedua (segitiga kiri bawah)
        -0.5f, -0.25f, // atas kiri
        -1.0f, -0.75f, // kiri bawah
         0.0f, -0.75f, // kanan bawah
        // Segitiga ketiga (segitiga kanan atas)
         0.5f,  0.25f, // atas kiri
         1.0f, -0.25f, // kiri bawah
         0.0f, -0.25f, // kanan bawah
        // Segitiga keempat (segitiga kanan bawah)
         0.5f, -0.25f, // atas kiri
         1.0f, -0.75f, // kiri bawah
         0.0f, -0.75f  // kanan bawah
    };

    unsigned int indices[] = {
        // Segitiga pertama
        0, 1, 2,
        // Segitiga kedua
        3, 4, 5,
        // Segitiga ketiga
        6, 7, 8,
        // Segitiga keempat
        9, 10, 11
    };

    // Initialize Vertex Array Buffer
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Setup vertex buffers
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 12 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    // Setting the layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, // Index untuk layout VAO
        2, // Ukuran vektor dari tipe data
        GL_FLOAT, // Tipe data
        GL_FALSE, // Dinormalisasi? Memetakan ke 0 - 255
        2 * sizeof(float), // Jarak antar verteks
        0                  // Offset
    );

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Lakukan di setiap frame di sini */
    glUseProgram(programId);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Ambil lebar dan tinggi layar
    int screenWidth, screenHeight;
    glfwGetWindowSize(window, &screenWidth, &screenHeight);

    // Hitung posisi segitiga berdasarkan lebar dan tinggi layar
    float offsetX = (float)screenWidth / 2.0f;
    float offsetY = (float)screenHeight / 2.0f;

    // Matriks transformasi untuk menggeser segitiga ke pusat layar
    mat4 model = glm::translate(mat4(1.0f), vec3(offsetX, offsetY, 0.0f));

    // Ambil lokasi uniform model dari program shader
    GLuint modelLoc = glGetUniformLocation(programId, "model");

    // Gambar empat segitiga
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
}


};