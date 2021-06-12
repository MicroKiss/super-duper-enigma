#include "CEH.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char const *argv[])
{
    CommonErrorHandler eh;
    std::ofstream myfile;

    /*lots of sueful code here*/
    //ez még csak kiírodik outputra
    eh.SetPriority(CommonErrorHandler::Priority::ERROR);
    eh << "nagynagyhiba0";
    eh.SetHandleError([&myfile](const std::string& str){myfile.open ("erroroutputfile.txt",std::ios::app); myfile << str << "\n";myfile.close();});
    //ez is még csak kiírodik outputra
    eh.SetPriority(CommonErrorHandler::Priority::NOTIFICATION);
    eh << "alma";

    /*lots of sueful code here again*/
    
    eh.SetPriority(CommonErrorHandler::Priority::ERROR);
    //ezek már fileba is meg outpura is.
    eh << "nagynagyhiba";
    eh << "nagynagyhiba2";


    return 0;
}
