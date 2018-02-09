#include "Renderer.h"

#include <GL/glew.h>

/*
 * Buffer Object
 */

void BufferObject::create(uint type, uint size, void* data, uint drawMode)
{
    m_objectType = type;
    glGenBuffers(1, &m_objectID);
    glBindBuffer(m_objectType, m_objectID);
    glBufferData(m_objectType, size, data, drawMode);
    glBindBuffer(m_objectType, 0);
}

void BufferObject::bind()const
{
    glBindBuffer(m_objectType, m_objectID);
}

void BufferObject::unbind()const
{
    glBindBuffer(m_objectType, 0);
}

uint BufferObject::getObjectID()const
{
    return m_objectID;
}
