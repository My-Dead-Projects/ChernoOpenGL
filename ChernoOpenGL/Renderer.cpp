#include "Renderer.h"

#include <GL/glew.h>
#include "GLError.h"

/*
 * Vertex Array Object
 */

void VertexArrayObject::create(uint index, uint size, uint type, bool normalized, uint stride, BufferObject vbo)
{
	GL(glGenVertexArrays(1, &m_objectID));
	GL(glBindVertexArray(m_objectID));
	GL(glEnableVertexAttribArray(0));
	GL(glBindBuffer(GL_ARRAY_BUFFER, vbo.getObjectID()));
	GL(glVertexAttribPointer(index, size, type, (normalized ? GL_TRUE : GL_FALSE), stride, nullptr));
}

uint VertexArrayObject::getObjectID()const
{
	return m_objectID;
}

/*
 * Buffer Object
 */

void BufferObject::create(uint type, uint size, void* data, uint drawMode)
{
    m_objectType = type;
    GL(glGenBuffers(1, &m_objectID));
    GL(glBindBuffer(m_objectType, m_objectID));
    GL(glBufferData(m_objectType, size, data, drawMode));
    GL(glBindBuffer(m_objectType, 0));
}

void BufferObject::bind()const
{
    GL(glBindBuffer(m_objectType, m_objectID));
}

void BufferObject::unbind()const
{
    GL(glBindBuffer(m_objectType, 0));
}

uint BufferObject::getObjectID()const
{
    return m_objectID;
}
