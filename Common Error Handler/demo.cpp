#include "CEH.hpp"
#include <iostream>
#include <fstream>
#include <cassert>

/* demo for the CommonErrorHandler*/

int main (int argc, char const *argv[])
{
    CEH::CommonErrorHandler eh;
    std::ofstream myfile;

    //this will be written to the std::cout because errors go to all 3 of the "channels"
    eh.SetPriority (CEH::Priority::ERROR);
    eh << "error1 ";

    //this will also be  written to the std::cout (see CEH.cpp)
    eh.SetPriority (CEH::Priority::NOTIFICATION);
    eh << "notification1 ";
    
    //set warning type handler so warnings and errors will als obe written to the file "erroroutputfile.txt" .
    eh.SetWarningHandle ([&myfile](const std::string& str){myfile.open ("erroroutputfile.txt",std::ios::app); myfile << str << "\n"; myfile.close();});

    //this will be written to the std::cout and also into the file "erroroutputfile.txt"
    eh.SetPriority(CEH::Priority::WARNING);
    eh << "warning1 " << "warning2 appended";

    try {
        throw CEH::Exception::TIMEOUT;
    } catch(const CEH::Exception& e) {
        //save current settings so we can restore them later
        CEH::Priority lastPriority = eh.GetPriority ();
        std::function<void(const std::string&)> lastErrorHandle = eh.GetErrorHandle ();

        //new temporary functionality
        eh.SetErrorHandle ([](const std::string& str){/*assert(false)*/;});
        
            //TIMEOUT is error everything else is warning
        if (e == CEH::Exception::TIMEOUT) 
            eh.SetPriority(CEH::Priority::ERROR);
        else 
            eh.SetPriority(CEH::Priority::WARNING);
        
        // get the description of the thrown error
        eh << CEH::GetErrorMessage(e);
        
        //restore settings
        eh.SetPriority (lastPriority);
        eh.SetErrorHandle (lastErrorHandle);
    }
    
    return 0;
}
