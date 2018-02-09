#ifndef Renderer_h
#define Renderer_h

#include "Constants.h"

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

class Renderer {
private:
    
public:
    
};

#endif
