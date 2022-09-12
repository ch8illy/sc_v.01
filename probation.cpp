
//  g++ probation.cpp core/utils.cpp core/blacklist.cpp core/terminator.cpp -o probation --static

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <ctime>
#include <chrono>
#include "core/utils.hpp"
#include "core/blacklist.hpp"
#include "core/terminator.hpp"



using namespace std;

#ifdef _WIN32
    #include <windows.h> 
//    #define HOST_PATH "C:\\Windows\\System32\\drivers\\etc\\hosts"
    void HideConsole()
    {
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    }

    void ShowConsole()
    {
       ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    }

#else

    #include <unistd.h>
//    #define HOST_PATH "src/hosts"
    unsigned int microsecond = 1000000;

#endif

#define FOR(i, k) for (int i=0 ; i<k ; i++)



string BLOCKPATH = "127.0.0.1";

string BLACKLISTFN = "src/blocklist";
string FORBIDDENFN = "src/forbiddenapps";
string BACKUPFN = "conf/hosts_bl";
string PROCESSFN = "conf/processes";


void display()
{
    string display_ = "start src/remind.jpg";
    system(display_.c_str());

}
    

int main()
{

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    Terminator TM(PROCESSFN, FORBIDDENFN);
    Blacklist bl(BLOCKPATH, BLACKLISTFN, BACKUPFN);

    int br; cout<<"block duration(s): "<<endl; cin >> br;

    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    auto ps = duration_cast<milliseconds>(t2 - t1);

    HideConsole();
    while(ps.count() < br*1000)
    {
        t2 = high_resolution_clock::now();
        ps = duration_cast<milliseconds>(t2 - t1);

        TM.kill();
        bl.block();

        #ifdef _WIN32
            Sleep(1500);
        #else
            sleep(1);
        #endif

    }   
    
    bl.unblock();
    ShowConsole();

    cout<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<"Probation is over..."<<endl;
    cout<<"Total Duration: "<< ps.count()/1000<<"s"<<endl;
    int x; cin >> x;
    cin.ignore(std::cin.rdbuf()->in_avail());
    cout <<"ctrl+c (if enter doesn't work) to exit\n";
    cin.ignore();

    return 0;
}
