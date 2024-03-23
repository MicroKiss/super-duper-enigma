#pragma once
#include <string>
#include <filesystem>


namespace curl {

std::filesystem::path GetCurlPath ();
std::string GetRequest (std::string const& url);
void Download (std::string const& url, std::filesystem::path const& loc);

}