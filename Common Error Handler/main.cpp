#include "CEH.hpp"
#include <iostream>
#include <fstream>
#include <cassert>

/* demo for the CommonErrorHandler*/

int main (int argc, char const *argv[])
{
    CEH::CommonErrorHandler eh;
    std::ofstream myfile;

    /*lots of sueful code here*/

    //ez még csak kiírodik outputra mert nincs külön errorhandle vagy warninghandle
    eh.SetPriority (CEH::Priority::ERROR);
    eh << "error1 ";


    //ez is még csak kiírodik outputra mert ez van a notificationhandlerben alapvetően (Lasd CEH.cpp)
    eh.SetPriority (CEH::Priority::NOTIFICATION);
    eh << "notification1 ";

    /*lots of sueful code here again*/
    
    //warning tipusu üzeneteket ezentúl appendáljuk egy "erroroutputfile.txt" fileba bele.
    eh.SetWarningHandle ([&myfile](const std::string& str){myfile.open ("erroroutputfile.txt",std::ios::app); myfile << str << "\n"; myfile.close();});
    //ezek már fileba is meg outpura is.
    eh.SetPriority(CEH::Priority::WARNING);
    eh << "warning1 " << "warning2 appended";



    try {
        throw CEH::Error::TIMEOUT;
    } catch(const CEH::Error& e) {
        //jelenelegi mukodes elmentese
        CEH::Priority lastPriority = eh.GetPriority ();
        std::function<void(const std::string&)> lastErrorHandle = eh.GetErrorHandle ();

        //uj mukodes ha ideiglenesen mashogy kellene kezelni egy errort
        eh.SetErrorHandle ([](const std::string& str){/*assert(false)*/;});
        
        if (e == CEH::Error::TIMEOUT) {
            //most a TIMEOUT legyen error különben csak minden mas warning

            eh.SetPriority(CEH::Priority::ERROR);
        } else {
            eh.SetPriority(CEH::Priority::WARNING);
        }
        
        eh << CEH::GetErrorMessage(e);
        //vissza tudjuk allitani a függvény elotti mukodesre
        eh.SetPriority (lastPriority);
        eh.SetErrorHandle (lastErrorHandle);
    }
    
    return 0;
}
