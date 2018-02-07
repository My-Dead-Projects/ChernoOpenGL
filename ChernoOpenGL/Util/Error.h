#ifndef Error_h
#define Error_h

#include <string>

class Error {
private:
    bool error;
    const std::string errorMessage;
    
    Error() : errorMessage("")
    {
        error = false;
    }
public:
    operator bool()
    {
        return error;
    }
    
    Error(const std::string& errorMessage) : errorMessage(errorMessage)
    {
        error = true;
    }
    
    const std::string getMessage()
    {
        return errorMessage;
    }
    
    static Error OK;
};

#endif
