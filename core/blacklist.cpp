#include "blacklist.hpp"

#ifdef _WIN32
    #include <windows.h> 
    #define HOST_PATH "C:\\Windows\\System32\\drivers\\etc\\hosts"
#else
    #include <unistd.h>
    #define HOST_PATH "src/hosts"
#endif


using namespace std;

Blacklist::Blacklist(string BlockPath,string blacklistfile, string backupfile)
{
    blockPath = BlockPath;
    backup_fn = backupfile;
    blacklist_fn = blacklistfile;


    Paragraph blacklist, hosts, T;
    setup();
}


void Blacklist::backUp(string fname, Paragraph T)
{
    erase_file(fname);
    ofstream backUp; backUp.open(fname);
    backUp << T.rawText(); backUp.close();
}

void Blacklist::block()
{

    T.processFileText(blacklist_fn);
    hosts.processFileText(HOST_PATH);

    blacklist.extends(T.toVector('\n'),'\n');

    vector<string> blackListEntries = blacklist.toVector('\n');

    // vector<string> defaults{"www.youtube.com","youtube.com","www.youtube.com","youtu.be","www.youtu.be","youtube-nocookie.com","www.youtube-nocookie.com","m.youtube.com","","","www.facebook.com","facebook.com","www.twitter.com","twitter.com","whatsapp.com","tiktok.com","","tetris.com","slither.io","moomoo.io","powerline.io","wings.io"};
    // for(int i=0; i<defaults.size(); i++)
    // {
    //     blackListEntries.push_back(defaults[i]);
    // }


    for(int i=0; i<blackListEntries.size(); i++){
        if(blackListEntries[i] != "" && blackListEntries[i] != " ")
        {
            blackListEntries[i] = blockPath+" "+blackListEntries[i];
        }
    }
    //cout<<"debug flag"<<endl; int n; cin >> n;


    T.fromVector(blackListEntries, '\n');
    hosts.extends(T.toVector('\n'),'\n');

    erase_file(HOST_PATH);
    hosts.writeFile(HOST_PATH);
}

void Blacklist::unblock()
{
    hosts.processFileText(backup_fn);
    hosts.writeFile(HOST_PATH);
}

void Blacklist::setup()
{
    hosts.processFileText(HOST_PATH);
    backUp(backup_fn, hosts);
}