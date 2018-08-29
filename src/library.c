#include "library.h"
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>


bool initalized = false;
GLuint shaderProgram;

void * initWindow(int width, int height, const char *title) {
    if (initalized) return NULL;
    if (!glfwInit()) return NULL;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) return NULL;
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) return NULL;
    initalized = true;

    const char *vertexShaderSource =
            "#version 330 core\n"
                    "layout (location = 0) in vec2 p_coord;\n"
                    "void main()\n"
                    "{\n"
                    "    gl_Position = vec4(p_coord.x, p_coord.y, 0.0, 1.0);\n"
                    "}";
    const char *fragmentShaderSource =
            "#version 330 core\n"
                    "uniform vec4 ourColor;\n"
                    "out vec4 color;\n"
                    "void main()\n"
                    "{\n"
                    "    color = ourColor;\n"
                    "}";

    GLint success;

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) return NULL;

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) return NULL;

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) return NULL;

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return window;
}

void setClearColor(float r, float g, float b, float alpha) {
    glClearColor(r, g, b, alpha);
}

void clear(void *handle) {
    glClear(GL_COLOR_BUFFER_BIT);
}

int eventOnClose(void *handle) {
    return glfwWindowShouldClose((GLFWwindow *)handle);
}

void pollEvents() {
    glfwPollEvents();
}

void terminate() {
    glfwTerminate();
}

void display(void *handle) {
    glfwSwapBuffers((GLFWwindow *) handle);
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b, float a) {
    GLfloat data[] = {x1, y1, x2, y2, x3, y3};
    GLuint VBO;
    glGenBuffers(1, &VBO);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, r, g, b, a);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void drawTriangleFan(int n, const float *x, const float *y, float r, float g, float b, float a) {
    GLfloat *data = malloc(sizeof(GLfloat) * n * 2);
    for (int i = 0; i < n; i++) {
        data[i * 2] = x[i];
        data[i * 2 + 1] = y[i];
    }
    GLuint VBO;
    glGenBuffers(1, &VBO);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * n * 2, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    free(data);

    glBindVertexArray(0);

    GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, r, g, b, a);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, n);
    glBindVertexArray(0);
}

void drawLine(float x1, float y1, float x2, float y2, float width, float r, float g, float b, float a, bool smooth) {
    GLfloat data[] = {x1, y1, x2, y2};
    GLuint VBO;
    glGenBuffers(1, &VBO);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    if (smooth) {
        glEnable(GL_LINE_SMOOTH);
    }

    GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, r, g, b, a);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
    if (smooth) {
        glDisable(GL_LINE_SMOOTH);
    }
}
