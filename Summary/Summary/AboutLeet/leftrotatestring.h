#pragma once
#include "publicdef.h"
class Solutionleftrotate
{
public:
    string rotate(std::string& s, int n)
    {
        int len = s.size();
        if (n >= len || n <= 0)return s;
        string left;
        string right;
        left = s.substr(0, n);
        right = s.substr(n, len);
        return right + left;
    }
};