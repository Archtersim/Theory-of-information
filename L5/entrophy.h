#ifndef ENTROPHY_H_INCLUDED
#define ENTROPHY_H_INCLUDED
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <map>
#include <algorithm>
#include <windows.h>

using namespace std;

enum class errcode
{
    GOOD=0,
    WRONGP=-1,
    WRONGGEN=-2,
};
unsigned char torus(unsigned char c);
void initnewalphabet(vector <unsigned char>alphabet,vector <string>& newalphabet,map <string,int> &hz,int dim,int &newrealsize);
double getpracticalentrophy(string fname,vector<unsigned char> alphabet,int dim,int modeRUS);
double entrophy(string fname,int dim);



#endif // ENTROPHY_H_INCLUDED
