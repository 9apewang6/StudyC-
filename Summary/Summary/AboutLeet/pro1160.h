#pragma once
#include "publicdef.h"
class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        map<char, int> warehouse;
        map<char, int> temphouse;
        int dictionlen = chars.size();
        int wordsize = words.size();
        if (wordsize == 0)return 0;
        int i, j;
        int totallen = 0;
        for (i = 0; i < dictionlen; i++)
        {
            warehouse[chars[i]]++;
        }
        int templen = 0;
        for (i = 0; i < wordsize; i++)
        {
            if (words[i].size() > dictionlen)continue;
            templen = 0;
            temphouse = warehouse;
            
            for (j = 0; j < words[i].size(); j++)
            {
                if (temphouse[words[i][j]] > 0)
                {
                    templen++;
                    temphouse[words[i][j]]--;
                }
                else
                {
                    templen = 0;
                    break;
                }
            }
            totallen += templen;
        }

        return totallen;

     }
};