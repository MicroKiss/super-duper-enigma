#pragma once

#include <iostream>
#include <functional>

class CommonErrorHandler
{
public:
    enum class Priority {
        NOTIFICATION = 0,
        WARNING      = 1,
        ERROR        = 2
    };

private:
    Priority priority;
    std::function<void(const std::string&)> HandleNotification;
    std::function<void(const std::string&)> HandleWarning;
    std::function<void(const std::string&)> HandleError;

public:
    void SetPriority                (Priority p);
    void SetHandleNotification      (std::function<void(const std::string&)> f);
    void SetHandleWarning           (std::function<void(const std::string&)> f);
    void SetHandleError             (std::function<void(const std::string&)> f);
    CommonErrorHandler              ();
    ~CommonErrorHandler             ();
    CommonErrorHandler& operator<<  (const std::string& str);
};

