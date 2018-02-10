#ifndef Renderer_h
#define Renderer_h

#include "Constants.h"

/*
* Abstracts both VBO and IBO
*/
class BufferObject {
private:
	uint m_objectID;
	uint m_objectType;
public:
	void create(uint type, uint size, void* data, uint drawMode);
	void bind()const;
	void unbind()const;
	uint getObjectID()const;
};

class VertexArrayObject {
private:
	uint m_objectID;
public:
	void create(uint index, uint size, uint type, bool normalized, uint stride, BufferObject vbo);
	uint getObjectID()const;
};

class Renderer {
private:
    
public:
    
};

#endif
