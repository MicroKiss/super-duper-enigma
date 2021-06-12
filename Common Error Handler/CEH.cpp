#include "CEH.hpp"

CommonErrorHandler::CommonErrorHandler ()
{
    HandleNotification = [](const std::string str){std::cout << str << "\n";};
    HandleWarning  = [](std::string){};
    HandleError = HandleWarning;
}

CommonErrorHandler::~CommonErrorHandler ()
{
}

void CommonErrorHandler::SetPriority (Priority p)
{
    priority = p;
}


void CommonErrorHandler::SetHandleNotification (std::function<void(const std::string&)> f) 
{
    HandleNotification = f;
}
void CommonErrorHandler::SetHandleWarning (std::function<void(const std::string&)> f) 
{
    HandleWarning = f;
}
void CommonErrorHandler::SetHandleError (std::function<void(const std::string&)> f) 
{
    HandleError = f;
}

CommonErrorHandler& CommonErrorHandler::operator<< (const std::string& str)
{

    /* Direkt nincs BREAK hogy az error mindenhol bekerüljön mert az a legszigorúbb*/
    switch (priority) {
        case Priority::ERROR :
            HandleError (str);
        case Priority::WARNING :
            HandleWarning (str);
        case Priority::NOTIFICATION :
            HandleNotification (str);
            break;
        default:
            break;
    }

    return *this;
}