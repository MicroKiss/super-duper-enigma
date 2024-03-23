#pragma once

#include <vector>
#include <filesystem>

std::filesystem::path GetSystem32Path ();
std::string ExecuteCommand(std::filesystem::path const& executablePath,std::vector<std::string> const& params);