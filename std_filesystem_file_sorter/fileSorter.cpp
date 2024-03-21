#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;


void Terminate (std::string const& msg, int errCode = 1) {
    std::cout << msg << std::endl;
    exit (errCode);
}


bool AskPermission (fs::path const& folder) {
    std::cout << "Are you sure you want to sort files by extensions in this folder:\n" << folder.string () << std::endl;
    std::cout << "Press (y/Y) to proceed: ";
    std::string answer;
    std::getline (std::cin, answer);
    return (answer == "y" || answer == "Y");
}

int main (int argc, char const *argv[]) {

    if (argc < 2)
        Terminate ("Give folder path as param");

    fs::path folder = argv[1];

    if (!fs::exists (folder) || !fs::directory_entry{folder}.is_directory ())
        Terminate ("Not an existing folder:" + folder.string ());

    if (!AskPermission (folder))
        Terminate ("Operation cancelled...", 0);
    

    size_t count {};

    for (auto dir : fs::directory_iterator (folder)) {
        if (dir.is_regular_file ()) {
            if (!fs::exists (dir.path ().parent_path () / dir.path ().extension ()))
                fs::create_directory (dir.path ().parent_path () / dir.path ().extension ());
            fs::rename (dir, dir.path ().parent_path () / dir.path ().extension () / dir.path ().filename ());
            ++count;
        }
    }

    std::cout << "Operation done, moved a total of: " << count << " file(s)\n";

    return 0;
}
