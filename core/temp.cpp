#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

#include "utils.hpp"

using namespace std;

string blockPath  ="0.0.0.0";

int main()
{
    Paragraph T, T2, BlackList;    

    T.processFileText("../src/blacklist");
    Paragraph hosts; hosts.processFileText("../src/hosts_bl");

    BlackList.extends(T.toVector('\n'),'\n');


    vector<string> blackListEntries = BlackList.toVector('\n');
    

    for(int i=0; i<blackListEntries.size(); i++){
        if(blackListEntries[i] != "" && blackListEntries[i] != " ")
        {
            blackListEntries[i] = blockPath+" "+blackListEntries[i];
        }
    }    T.fromVector(blackListEntries, '\n');

    cout<<hosts.rawText()<<endl;
    hosts.extends(T.toVector('\n'),'\n');

    cout<<hosts.rawText()<<endl;

    // erase_file("../src/hosts_bl");
    // hosts.writeFile("../src/hosts_bl");
    
}