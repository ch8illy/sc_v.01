#include "terminator.hpp"
#include <regex>

#define FOR(i, k) for (int i=0 ; i<k ; i++)

using namespace std;

Terminator :: Terminator(string ProcessName, string ForbiddenName)
{
    process_fn = ProcessName;
    forbidden_fn = ForbiddenName;
}

void Terminator :: terminate(string process)
{
    string cmd = ("taskkill /F /IM "+process);

    cout<<"Executing: "<<"kill "+process<<";"<<endl; 
    cout<<"Process: "<<cmd<<endl;   

    if(system(cmd.c_str()))
    {
        cout<<"COMMAND PROCESS SUCCESSFUL"<<endl;
    }else
    {
        cout<<"COMMAND PROCESS FAILED"<<endl;
    }
    cout<<"Termination Completed... : "<<process<<";"<<endl;
}


void Terminator::kill() 
{
    erase_file(process_fn);

    string tasklist = ("tasklist >> "+process_fn);
    system( tasklist.c_str() );
    
    Paragraph tasks; tasks.processFileText(process_fn);

    vector<string> Tl = tasks.toVector('\n');

    // vector<string> defaults{"HD-","steam","Zoom","msedge","Taskmgr","RiotClientServices","VALORANT"};
    
    // for(int i=0; i<defaults.size(); i++)
    // {
    //     Tl.push_back(defaults[i]);
    // }

    string sip ("System Idle Process");

    int rmvi = 0;

    FOR(i, Tl.size())
    {
        if (Tl[i].find(sip) != string::npos)
        {
            rmvi = i;
        }

    }

    int j_ = Tl.size() - rmvi -1;
    while(Tl.size() > j_)
    {
        Tl.erase(Tl.begin());
    }

    regex re("\\s{2,}");
    FOR(i, Tl.size()) Tl[i] = regex_replace(Tl[i], re, " "); 
    
    tasks.fromVector(Tl, ' '); Tl = tasks.toVector(' ');
    vector<string> xE;
    int s = Tl.size();


    FOR(i, s)
    {
        if (in(Tl[i],".exe"))
        {
            xE.push_back(Tl[i]);
        }
    }

    T.processFileText(forbidden_fn);
    Forbidden.extends(T.toVector('\n'), '\n');
    vector<string> T_ = Forbidden.toVector('\n');

    FOR(i, xE.size())
    {
        FOR(j, T_.size())
        {
            if(in(xE[i], T_[j]))
            {
                terminate(xE[i]);
            }
        }
    }

    
}