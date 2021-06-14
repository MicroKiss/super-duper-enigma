#pragma once

#include <iostream>
#include <functional>

namespace CEH
{
    enum class Priority {
        NOTIFICATION = 0,
        WARNING      = 1,
        ERROR        = 2
    };

    enum class Error {
        NOPERMISSIONTOWRITE = 0,
        NOPERMISSIONTOREAD  = 1,
        BADPARAMS           = 2,
        TIMEOUT             = 3,
        //etc.
        
    };

    std::string GetErrorMessage     (const Error& e);

    class CommonErrorHandler
    {
    private:
        Priority priority;
        std::function<void(const std::string&)> notificationHandle;
        std::function<void(const std::string&)> warningHandle;
        std::function<void(const std::string&)> errorHandle;

    public:
        CommonErrorHandler              ();
        ~CommonErrorHandler             ();

        void SetPriority                (Priority p);
        void SetNotificationHandle      (std::function<void(const std::string&)> f);
        void SetWarningHandle           (std::function<void(const std::string&)> f);
        void SetErrorHandle             (std::function<void(const std::string&)> f);

        Priority                                GetPriority                () const;        
        std::function<void(const std::string&)> GetNotificationHandle      () const;
        std::function<void(const std::string&)> GetWarningHandle           () const;
        std::function<void(const std::string&)> GetErrorHandle             () const;

        CommonErrorHandler&                     operator<<                 (const std::string& str);
    };

    
} // namespace CEH

