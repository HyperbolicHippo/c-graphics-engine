#define GLEW_NO_GLU
#include <GL/glew.h>

#include <stdio.h>

#include "shader.h"
#include "file_utils.h"


/* ---------- SHADER ---------- */
Shader shader_create(int type, const char* path) {
    // create and return a Shader struct
    uint32_t handle = glCreateShader(type);
    
    Shader shader;
    shader.type = type;
    shader.handle = handle;

    const char* source = read_file(path);
    glShaderSource(handle, 1, &source, NULL);
    free(source);

    return shader;
}

void shader_compile(const Shader* shader) {
    // compile the given shader and check for errors
    glCompileShader(shader->handle);
    int success;
    char info_log[512];
    glGetShaderiv(shader->handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader->handle, 512, NULL, info_log);
        printf(info_log);
    }
}

void shader_delete(const Shader* shader) {
    // delete the given shader
    glDeleteShader(shader->handle);
}
/* ---------------------------- */


/* ------ SHADER PROGRAM ------ */
ShaderProgram shader_program_create(const Shader* vertex, const Shader* fragment) {
    // create a return a shader program using the given vertex and fragment shaders
    uint32_t handle = glCreateProgram();

    ShaderProgram program;
    program.handle = handle;
    program.vertex = *vertex;
    program.fragment = *fragment;

    glAttachShader(handle, vertex->handle);
    glAttachShader(handle, fragment->handle);

    return program;
}

void shader_program_link(const ShaderProgram* program) {
    // link the given shader program
    glLinkProgram(program->handle);
    int success;
    char info_log[512];
    glGetProgramiv(program->handle, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program->handle, 512, NULL, info_log);
        printf(info_log);
    }
}

void shader_program_validate(const ShaderProgram* program) {
    // validate the given shader program
    glValidateProgram(program->handle);
    int success;
    char info_log[512];
    glGetProgramiv(program->handle, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program->handle, 512, NULL, info_log);
        printf(info_log);
    }
}

void shader_program_use(const ShaderProgram* program) {
    // tell opengl to use the given shader program
    glUseProgram(program->handle);
}

void shader_program_delete(const ShaderProgram* program) {
    // delete the given shader program
    glDeleteProgram(program->handle);
}

/* ---------------------------- */