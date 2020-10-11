#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>
#include <string>

const int ctot(36);
const int maxSlen(54);

int ops = 0;

typedef struct palInfo
{
    uint8_t length;
    uint8_t startpos;
} PalInfo;

PalInfo longestPalFind(std::string s)
{
    //std::cout << "passed s is \n    ";
    //for (auto c : s)
    //    std::cout << c << " ";
    //std::cout << "\n";
    PalInfo result;
    size_t length = 0;
    result.startpos = 0;
    result.length = s.length();
    length = s.length();
    std::array<std::array<uint8_t, maxSlen>, ctot> posits{0};
    std::array<std::array<bool, maxSlen>, maxSlen> pairs{false};
    ops += 6;
    //-------------------------------
    // log positions of each char
    int index = 0;
    for (auto it = s.begin(); it != s.end(); it++, ++index)
    {
        // std::cout << "[" << int(uint8_t(*it)-'a') << "]["
        //     << int(posits[uint8_t(*it)-'a'][0]+1)
        //     << "] = " << index << "\n";
        posits[uint8_t(*it) - 'a'][++posits[uint8_t(*it) - 'a'][0]] = index;
        ops++;
    }
    // show log of char positions
     for(int i=0; i<ctot; ++i)
     {
         std::cout << ((i<=('z'-'a'))?char(i+'a'):char(i-('z'-'a')-1+'0')) << "-->";
         for(int j=0; j<=posits[i][0]; ++j)
             std::cout << int(posits[i][j]) << ",";
         std::cout << "\n";
     }

    //--------------------------
    // fill in array of pairs
    for (int i = 0; i < ctot; ++i)
    {
        // std::cout << char(i+'a') << "#" << int(posits[i][0]) << "-->";
        for (int j = 0; j < posits[i][0]; ++j)
        {
            for (int k = j + 2; k <= posits[i][0]; ++k)
            {
                // std::cout << "[" << int(posits[i][j+1]) << "][" << int(posits[i][k])
                // << "]:";
                pairs[posits[i][j + 1]][posits[i][k]] = true;
                ops++;
            }
            // std::cout << "\n";
        }
    }
    // show pairs array with labels
    std::cout << "\n    ";
    for (auto c : s)
        std::cout << c << " ";
    std::cout << "\n   ";
    for (int i = 0; i < maxSlen; ++i)
        std::cout << " " << i % 10;
    std::cout << "\n";
    for (int i = 0; i < maxSlen; ++i)
    {
        std::cout << i % 10 << ": ";
        for (int j = 0; j < maxSlen; ++j)
        {
            std::cout << " " << char(pairs[i][j] ? 'X' : ((j<i+1)?'|':'-'));
        }
        std::cout << "\n";

    }

    // go down diagonals checking how many consecutive pairs
    int maxLen = 0;
    int palLen = 0;
    int start = 0;

    //---------------------------------------------
    // first check for palindromes of even length
    int offset = 0;
    int i = 0;
    ops += 5;
    while ((i - offset) >= 0 && (i + offset + 1) <= length)
    {
        //std::cout << "[" << i - offset << "][" << i + offset + 1 << "]"
        //          << char(pairs[i - offset][i + offset + 1] ? '#' : '-');
        //std::cout << "i is " << i << " and offset is " << offset << "\n";
        ops++;
        if (pairs[i - offset][i + offset + 1])
        {
            palLen += 2;
            start = i - offset;
            //std::cout << "\n";
            //std::cout << "[" << i - offset << "][" << i + offset + 1 << "]";
            offset++;
            ops += 3;
            //std::cout << "found " << s.substr(start, palLen) << "\n";
            if (palLen > maxLen)
            {
                maxLen = palLen;
                result.length = palLen;
                result.startpos = start;
                ops += 4;
            }
            if (start == 0)
            {
                i++;
                offset = 0;
                ops += 2;
            }
        }
        else
        {
            i++;
            offset = 0;
            palLen = 0;
            ops++;
        }
    }
    //std::cout << "palLen and maxLen are " << palLen << " : " << maxLen << "\n";
    //std::cout << "max " << s.substr(result.startpos, maxLen) << "\n";

    //-------------------------------------------
    // now check for palindromes of odd length
    offset = 0;
    i = 0;
    palLen = 1;
    ops += 3;
    while ((i - offset) >= 0 && (i + offset + 2) <= length)
    {
        //std::cout << "[" << i - offset << "][" << i + offset + 2 << "]"
        //          << char(pairs[i - offset][i + offset + 2] ? '#' : '-');
        //std::cout << "i is " << i << " and offset is " << offset << "\n";
        ops++;
        if (pairs[i - offset][i + offset + 2])
        {
            palLen += 2;
            start = i - offset;
            //std::cout << "\n";
            //std::cout << "[" << i - offset << "][" << i + offset + 2 << "]";
            offset++;
            ops += 3;
            //std::cout << "found " << s.substr(start, palLen) << "\n";
            if (palLen > maxLen)
            {
                maxLen = palLen;
                result.length = palLen;
                result.startpos = start;
                ops += 4;
            }
            if (start == 0)
            {
                i++;
                offset = 0;
                ops += 2;
            }
        }
        else
        {
            i++;
            offset = 0;
            palLen = 1;
            ops += 3;
        }
    }

    //std::cout << "max " << s.substr(result.startpos, maxLen) << "\n";
    //std::cout << "passed s is \n    ";
    //for (auto c : s)
    //    std::cout << c << " ";
    //std::cout << "\n";

    return result;
}
int main()
{
    //std::string instr{"ffffTo efferreffe use an unoverrevonu Environment"};
    std::string instr{ "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba" };
    //std::string instr{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" };
    //std::string instr{"Doc, note, I dissent. A fast never prevents a fatness. I diet on cod.abDoc, note, I dissent. A fast never prevents a fatness. I diet on cod."};
    //std::string instr{"abac abadebb edACaba"};
    std::string newstr{""};
    for (auto c : instr)
        if ((c >= 'A' && c <= 'Z') or (c >= 'a' && c <= 'z'))
        {
            newstr += tolower(c);
           // ops++;
        }
        else if (c >= '0' && c <= '9')
        {
            newstr += c - '0' + 'z' + 1;
            //ops++;
        }
    std::cout << newstr << "\n";
    auto result = longestPalFind(newstr);
    std::cout << "longest palindrome was " << newstr.substr(result.startpos, result.length);
    std::cout << "\n" << ops << " total operations\n";
}
