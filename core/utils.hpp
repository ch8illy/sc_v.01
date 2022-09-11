#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Paragraph
{
    public:
        Paragraph();
        Paragraph(string text);
        
        void processFileText(string fname);
        void writeFile(string fname);
        void fromVector(vector<string> s, char splitter);

        void extends(string s);
        void extends(Paragraph other);
        void extends(Paragraph other, char separator);
        void extends(vector<string> s, char separator);

        string rawText();
        vector<string> toVector(char splitter);
        string T_xt;

};

void erase_file(string fname);
bool in(string s1, string s2);

#endif
