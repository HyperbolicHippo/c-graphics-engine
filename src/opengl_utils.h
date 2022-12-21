#ifndef _OPENGL_UTILS_H
#define _OPENGL_UTILS_H

#include <stdint.h>

typedef uint32_t VertexArray;
typedef struct VertexBuffer {
    uint32_t handle;
    const void* data;
    int usage;
};

VertexArray vertex_array_create();
void vertex_array_bind(VertexArray vao);
void vertex_array_delete(VertexArray vao);

VertexBuffer vertex_buffer_create();
void vertex_buffer_bind(const VertexBuffer* vbo);
void vertex_buffer_data(const VertexBuffer* vbo);
void vertex_buffer_delete(const VertexBuffer* vbo);

#endif // _OPENGL_UTILS_H
