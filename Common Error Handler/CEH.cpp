#include "CEH.hpp"

namespace CEH
{

std::string GetErrorMessage (const Exception& e)
{
    switch (e) {
        case Exception::NOPERMISSIONTOWRITE:
            return "No permission to write";
        case Exception::NOPERMISSIONTOREAD:
            return "No permission to read";
        case Exception::BADPARAMS:
            return "Bad params";
        case Exception::TIMEOUT:
            return "Timeout has happened";
    }
    return "unknown error";
}


CommonErrorHandler::CommonErrorHandler ()
{
    SetNotificationHandle ([](const std::string str){std::cout << str << "\n";});
    SetWarningHandle ([](std::string){});
    SetErrorHandle (GetWarningHandle ());
}


CommonErrorHandler::~CommonErrorHandler ()
{
}


void CommonErrorHandler::SetPriority (Priority p)
{
    priority = p;
}


void CommonErrorHandler::SetNotificationHandle (std::function<void(const std::string&)> f) 
{
    notificationHandle = f;
}


void CommonErrorHandler::SetWarningHandle (std::function<void(const std::string&)> f) 
{
    warningHandle = f;
}


void CommonErrorHandler::SetErrorHandle (std::function<void(const std::string&)> f) 
{
    errorHandle = f;
}


Priority CommonErrorHandler::GetPriority () const
{
    return priority;
}


std::function<void(const std::string&)> CommonErrorHandler::GetNotificationHandle      () const
{
    return notificationHandle;
}


std::function<void(const std::string&)> CommonErrorHandler::GetWarningHandle           () const
{
    return warningHandle;
}


std::function<void(const std::string&)> CommonErrorHandler::GetErrorHandle             () const
{
    return errorHandle;
}


CommonErrorHandler& CommonErrorHandler::operator<< (const std::string& str)
{
    // see that there is no breaks in the switch cases so for the stronger cases more handle will be called
    switch (priority) {
        case Priority::ERROR :
            errorHandle (str);
        case Priority::WARNING :
            warningHandle (str);
        case Priority::NOTIFICATION :
            notificationHandle (str);
        default:
            break;
    }

    return *this;
}

} // namespace CEH