#define GLFW_INCLUDE_NONE
#define GLEW_NO_GLU
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "file_utils.h"
#include "shader.h"


void glfw_error_callback(int code, const char* description) {
    printf("GLFW ERROR : %i : %s\n", code, description);
}


void glfw_window_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


GLFWwindow* create_glfw_window_and_opengl_context(int width, int height, const char* title) {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        return NULL;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    GLFWwindow* to_return = glfwCreateWindow(width, height, title, NULL, NULL);
    if (to_return == NULL) {
        // may seem redundant as returning to_return would return NULL anyway, however
        // if NULL, then further operations cannot happen
        printf("Failed to create glfw window.\n");
        return NULL;
    }

    glfwSetWindowSizeCallback(to_return, glfw_window_resize_callback);

    glfwMakeContextCurrent(to_return);
    glewInit();

    return to_return;
}


int main(void) {
    printf("GLFW Version: %s\n", glfwGetVersionString());
    GLFWwindow* glfw_window = create_glfw_window_and_opengl_context(1366, 768, "C Game Engine");
    if (glfw_window == NULL) {
        return EXIT_FAILURE;
    }


    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 7 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader vertex_shader = shader_create(GL_VERTEX_SHADER, "res/shaders/shader.vert");
    shader_compile(&vertex_shader);
    Shader fragment_shader = shader_create(GL_FRAGMENT_SHADER, "res/shaders/shader.frag");
    shader_compile(&fragment_shader);

    ShaderProgram shader_program = shader_program_create(&vertex_shader, &fragment_shader);
    shader_program_link(&shader_program);
    shader_program_validate(&shader_program);
    shader_program_use(&shader_program);

    // unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // char* vertex_src = read_file("res/shaders/shader.vert");
    // glShaderSource(vertex_shader, 1, &vertex_src, NULL);
    // free(vertex_src);
    // glCompileShader(vertex_shader);
    // int success;
    // char info_log[512];
    // glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //     glGetShaderInfoLog(vertex_shader, 512, (void*)0, info_log);
    //     printf(info_log);
    // }
    
    // unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    // char* fragment_src = read_file("res/shaders/shader.frag");
    // glShaderSource(fragment_shader, 1, &fragment_src, NULL);
    // free(fragment_src);
    // glCompileShader(fragment_shader);
    // glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //     glGetShaderInfoLog(fragment_shader, 512, (void*)0, info_log);
    //     printf(info_log);
    // }

    // unsigned int shader_program = glCreateProgram();
    // glAttachShader(shader_program, vertex_shader.handle);
    // glAttachShader(shader_program, fragment_shader.handle);
    // glLinkProgram(shader_program);
    // glValidateProgram(shader_program);
    // glUseProgram(shader_program);


    while (!glfwWindowShouldClose(glfw_window))
    {
        glClearColor(0.3f, 0.7f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }

    glfwDestroyWindow(glfw_window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
