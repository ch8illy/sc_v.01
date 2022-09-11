#include "utils.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

Paragraph::Paragraph(string text)
{
    T_xt = text;
}

Paragraph::Paragraph(){T_xt = "";}

string Paragraph::rawText(){ return T_xt; }

void Paragraph::processFileText(string fname)
{
    
    ifstream infile; infile.open(fname);
    stringstream ss; ss << infile.rdbuf();

    T_xt = ss.str();
}

void Paragraph::writeFile(string fname)
{
    ofstream f; f.open(fname);
    f << T_xt; f.close();

}

vector<string> Paragraph::toVector(char splitter)
{
    stringstream ss(T_xt); string tmp;
    vector<string> texts;

    while(getline(ss,tmp,splitter))
    {
        texts.push_back(tmp);
    }

    return texts;

}

void Paragraph::fromVector(vector<string> s,  char splitter)
{
    T_xt = "";
    for(int i=0; i<(s.size()-1); i++)
    {
        T_xt +=s[i]+splitter;
    }

    T_xt +=s[s.size()-1];
}

void Paragraph::extends(string s){this->T_xt+=s;}
void Paragraph::extends(Paragraph other){this->T_xt += other.rawText();}
void Paragraph::extends(Paragraph other, char separator)
{
    T_xt += separator+other.rawText();
}


void Paragraph::extends(vector<string> s, char seperator)
{
    vector<string> T = this->toVector(seperator);


    for(string s_ : s)
    {
        if (count(T.begin(), T.end(), s_)) 
        {
            continue;
        }else{
            T.push_back(s_);
        }
    }
    
    this->fromVector(T, seperator);

}

void erase_file(string fname){ofstream fd; fd.open(fname, std::ofstream::out | std::ofstream::trunc); fd.close();}

bool in(string s1, string s2){return s1.find(s2) != string::npos;}

