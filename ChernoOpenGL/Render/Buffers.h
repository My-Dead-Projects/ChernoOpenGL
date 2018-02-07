#ifndef Buffers_h
#define Buffers_h

#include "GLError.h"

void bindBuffer(uint type, uint bufferObject)
{
    GL(glBindBuffer(type, bufferObject));
}

void unbindBuffer(uint type)
{
    GL(glBindBuffer(type, 0));
}

uint createBuffer(uint type,
                  size_t size,
                  const void* data,
                  uint drawingHint)
{
    uint bufferObject = 0;
    GL(glGenBuffers(1, &bufferObject));
    
    bindBuffer(type, bufferObject);
    GL(glBufferData(type, size, data, drawingHint));
    unbindBuffer(type);
    return bufferObject;
}

uint createVertexArrayObject(uint vbo)
{
    uint vao = 0;
    GL(glGenVertexArrays(1, &vao));
    GL(glBindVertexArray(vao));
    GL(glEnableVertexAttribArray(0));
    
    bindBuffer(GL_ARRAY_BUFFER, vbo);
    GL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL));
    unbindBuffer(GL_ARRAY_BUFFER);
    return vao;
}

#endif
