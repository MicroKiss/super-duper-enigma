#include "Curl.hpp"

#include "SystemUtils.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace curl {

std::filesystem::path GetCurlPath () {
    return GetSystem32Path () / "curl.exe";
}

std::string GetRequest (std::string const &url) {
    return ExecuteCommand (GetCurlPath (), {"-X", "GET", url});
}

void Download (std::string const &url, std::filesystem::path const &loc) {
    std::filesystem::create_directories (loc.parent_path ());
    
    ExecuteCommand (GetCurlPath (), {"-o", loc.string (), url});
}

}