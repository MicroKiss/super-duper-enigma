#include "Curl.hpp"
#include <iostream>

int main (int argc, char const *argv[]) {

    try {
        std::cout << curl::GetRequest (R"(https://raw.githubusercontent.com/MicroKiss/express/main/README.md)");
        curl::Download (R"(https://raw.githubusercontent.com/MicroKiss/super-duper-enigma/master/LengthUnits/readme.md)", {"D:\\Dev\\proba\\asd\\casd\\basd.txt"});
    } catch (const std::exception &e) {
        std::cerr << e.what () << '\n';
    }
    return 0;
}
