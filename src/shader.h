#ifndef _SHADER_H
#define _SHADER_H

#include <stdint.h>

typedef struct Shader {
    uint32_t handle;
    int type;
} Shader;

typedef struct ShaderProgram {
    uint32_t handle;
    Shader vertex;
    Shader fragment;
} ShaderProgram;

Shader shader_create(int type, const char* path);
void shader_compile(const Shader* shader);
void shader_delete(const Shader* shader);

ShaderProgram shader_program_create(const Shader* vertex, const Shader* fragment);
void shader_program_link(const ShaderProgram* program);
void shader_program_validate(const ShaderProgram* program);
void shader_program_use(const ShaderProgram* program);
void shader_program_delete(const ShaderProgram* program);

#endif // _SHADER_H
