#include "CEH.hpp"

namespace CEH
{

std::string GetErrorMessage (const Error& e)
{
    switch (e) {
    case Error::NOPERMISSIONTOWRITE:
        return "Cannot write to the output location";
        break;
    case Error::NOPERMISSIONTOREAD:
        return "I can't read that";
        break;
    case Error::BADPARAMS:
        return "Bad params mate";
        break;
    case Error::TIMEOUT:
        return "Friend app takes too long :'(";
        break;
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

    /* Direkt nincs BREAK hogy az error mindenhova bekerüljön mert az a legszigorubb*/
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