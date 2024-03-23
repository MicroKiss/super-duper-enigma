#include "SystemUtils.hpp"

#include <array>
#include <stdexcept>
#include <Windows.h>


class HandleManager {
public:
    HandleManager() noexcept {}
    ~HandleManager() noexcept {
        if (handle != NULL && handle != INVALID_HANDLE_VALUE)
            CloseHandle(handle); 
    }
    HandleManager(HandleManager&& other) noexcept {
        handle = other.handle;
        other.handle = NULL;
    };
    
    HandleManager& operator=(HandleManager&& other) noexcept {
        if (&handle == &other.handle)
            return *this;
        handle = other.handle;
        other.handle = NULL;
    };

    void Close () {
        if (handle != NULL && handle != INVALID_HANDLE_VALUE)
            CloseHandle(handle); 
        handle = NULL;
    }

    operator HANDLE () const {
        return handle;
    }

    HANDLE* operator& () {
        return &handle;
    }

    // Disable copy and move semantics
    HandleManager(const HandleManager&) = delete;
    HandleManager& operator=(const HandleManager&) = delete;

private:
    HANDLE handle;
};


std::filesystem::path GetSystem32Path () {
    char system32Path[MAX_PATH];
    if (GetSystemDirectoryA(system32Path, MAX_PATH) == 0)
        throw std::runtime_error("GetSystemDirectory failed");
    return std::filesystem::path {system32Path};
}


std::string ExecuteCommand(std::filesystem::path const& executablePath, std::vector<std::string> const& params) {
    std::array<char, 128> buffer;
    std::string result;
    DWORD bytesRead;
    HandleManager hReadPipe;
    HandleManager hWritePipe;
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;
    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
        throw std::runtime_error("CreatePipe failed");
    }

    SetHandleInformation(hReadPipe, HANDLE_FLAG_INHERIT, 0);

    std::string command = executablePath.string ();
    for (const auto& param : params) {
        command += " " + param;
    }
    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = hWritePipe;
    //si.hStdError = hWritePipe;
    if (!CreateProcessA(NULL, const_cast<LPSTR>(command.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
        throw std::runtime_error("CreateProcess failed");

    //if it's not cloes ReadFile won't ever stop
    hWritePipe.Close ();

    while (true) {
        if (!ReadFile(hReadPipe, buffer.data(), buffer.size(), &bytesRead, NULL)) {
            DWORD lastError = GetLastError();
            if (lastError == ERROR_BROKEN_PIPE) {
                // Pipe closed, child process has terminated
                break;
            } else {
                // Some other error occurred
                throw std::runtime_error("ReadFile failed");
            }
        }

        if (bytesRead == 0) {
            // No more data available, child process has terminated
            break;
        }

        result.append(buffer.data(), bytesRead);
    }
    if (WaitForSingleObject(pi.hProcess, INFINITE) != WAIT_OBJECT_0) {
        throw std::runtime_error("WaitForSingleObject failed");
    }

    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        throw std::runtime_error("GetExitCodeProcess failed");
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode != 0)
        throw std::runtime_error("Process returned non-zero exit code");
    
    return result;
}