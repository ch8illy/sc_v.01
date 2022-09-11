#ifndef BLACKLIST_H
#define BLACKLIST_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include "utils.hpp"

using namespace std;

class Blacklist
{
    public:
        Blacklist(string BlockPath,string blacklistfile, string backupfile);
        
        void backUp(string fname, Paragraph T);
        void block();
        void unblock();
        void setup();
        
        string blockPath;
        string backup_fn;
        string blacklist_fn;
        Paragraph blacklist, hosts, T;

};


#endif
