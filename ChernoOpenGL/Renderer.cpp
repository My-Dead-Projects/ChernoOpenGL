#include "Renderer.h"

#include <GL/glew.h>
#include "GLError.h"

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
