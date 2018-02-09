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
    
    std::string message()
    {
        return errorMessage;
    }
    
    static Error&& OK()
    {
        Error e;
        return std::move(e);
    }
};

#endif 
