#ifndef Buffers_h
#define Buffers_h

#include "GLError.h"

uint createAndBindBuffer(uint type, size_t size, const void* data, uint drawingHint)
{
    uint bufferObject = 0;
    GL(glGenBuffers(1, &bufferObject));
    GL(glBindBuffer(type, bufferObject));
    GL(glBufferData(type, size, data, drawingHint));
    return bufferObject;
}

uint createAndBindVAO(uint vbo)
{
    uint vao = 0;
    GL(glGenVertexArrays(1, &vao));
    GL(glBindVertexArray(vao));
    GL(glEnableVertexAttribArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL));
    return vao;
}

#endif
