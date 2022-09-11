#ifndef TERMINATOR_H
#define TERMINATOR_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include "utils.hpp"

using namespace std;

class Terminator
{
    public:
        Terminator(string ProcessName, string ForbiddenName);

        void terminate(string process);
        void kill();

        string process_fn;
        string forbidden_fn;

        Paragraph Forbidden, T;

};


#endif
