#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <map>
using namespace std;

enum class errcode
{
    GOOD=0,
    WRONGP=-1,
    WRONGGEN=-2,
};

errcode genfile(ofstream &F,vector<char> alphabet,vector<double> chances,int sizeoffile)
{
    double checkP=0;
    for(int i=0; i<chances.size(); i++)
    {
        checkP+=chances[i];
    }
    if(checkP<1-0.0001||checkP>1+0.0001||alphabet.size()!=chances.size())
    {
        return errcode::WRONGP;
    }
    double accuracy=100000;
    for(int i=0; i<sizeoffile; i++)
    {
        double gen=(rand()*rand()%(int)accuracy)/accuracy;
        double interval=0;
        int indgen=-1;
        for(int j=0; j<chances.size(); j++)
        {
            if(gen>=interval&&gen<(interval+chances[j]))
                indgen=j;
            interval+=chances[j];
        }
        if(indgen!=-1)
            F<<alphabet[indgen];
        else
            return errcode::WRONGGEN;
    }
    return errcode::GOOD;
}

int calcchances(vector<double> oldchances,vector<double> &newchances,int dim)
{
    if (dim==1)
        newchances=oldchances;
    vector<double> tmpchances=oldchances;
    if (dim>1)
    {
        for(int i=1; i<dim; i++)
        {
            for(int j=0; j<oldchances.size(); j++)
            {
                for(int k=0; k<tmpchances.size(); k++)
                {
                    newchances.push_back(oldchances[j]*tmpchances[k]);
                }
            }
            tmpchances=newchances;
            if(i==(dim-1))
                break;
            else
                newchances.clear();
        }
    }
}

double gettheoreticalentrophy(vector<double> chances,int dim)
{
    double res=0;
    vector <double> newchances;
    calcchances(chances,newchances,dim);
    for(int i=0; i<newchances.size(); i++)
    {
        res+=-log2(newchances[i])*newchances[i];
    }
    return res/(double)dim;
}

void initnewalphabet(vector <char>alphabet,vector <string>& newalphabet,map <string,int> &hz,int dim,int &newrealsize)
{

    if (dim==1)
    {
        for(int i=0; i<alphabet.size(); i++)
        {
            string s;
            s.push_back(alphabet[i]);
            hz[s]=0;
            newalphabet.push_back(s);
        }

        newrealsize=alphabet.size();
    }

    vector<string> tmp;
    for(int i=0; i<alphabet.size(); i++)
    {
        string s;
        s.push_back(alphabet[i]);
        tmp.push_back(s);
    }
    vector<string> tmpalphabet=tmp;
    vector<string> oldalphabet=tmp;
    if (dim>1)
    {
        for(int i=1; i<dim; i++)
        {
            for(int j=0; j<oldalphabet.size(); j++)
            {
                for(int k=0; k<tmpalphabet.size(); k++)
                {
                    newalphabet.push_back(oldalphabet[j]+tmpalphabet[k]);
                }
            }
            tmpalphabet=newalphabet;
            if(i==(dim-1))
                break;
            else
                newalphabet.clear();
        }
    }
    if(dim>=2)
        newrealsize=newalphabet.size();
    if(dim>=2)
        for(int i=0; i<newalphabet.size(); i++)
        {
            hz[newalphabet[i]]=0;
        }
    return;
};


double getpracticalentrophy(string fname,int sizeoffile,vector<char> alphabet,int dim)
{
    ifstream F1;
    char c;
    map <string,int>hz;
    char word[dim];
    int newrealsize=0;
    vector <string> newalphabet;
    initnewalphabet(alphabet,newalphabet,hz,dim,newrealsize);

    int realsize=0;
    F1.open(fname,ios::binary);

    vector<string> dictionary;
    if(!F1.read(word,dim))
        return -4;

    while(F1.get(c))
    {
        string s;
        for(int i=0; i<dim; i++)
            s.push_back(word[i]);
        hz[s]++;
        realsize++;
        dictionary.push_back(s);
        for(int i=1; i<dim; i++)
            word[i-1]=word[i];
        word[dim-1]=c;


    }

    string st;
        for(int i=0; i<dim; i++)
            st.push_back(word[i]);
        hz[st]++;
        realsize++;
        dictionary.push_back(st);

    F1.close();
    double res=0;

    for(int j=0; j<newrealsize; j++)
    {

        double p=(double)hz[newalphabet[j]]/(double)realsize;

        if(p>0)res=res-log2(p)*p;

    }
    return res/(double)dim;
}

int main()
{
    srand(time(NULL));
    vector<char> alphabet {'a','b','c','d'};
    vector <double> chances(4,0.25);
    vector <double> entrophyT;
    vector <double> entrophyP;
    int sizeoffile=1<<20;
    ofstream F1;
    F1.open("F1.txt",ios::binary);
    if(genfile(F1,alphabet,chances,sizeoffile)!=errcode::GOOD)
    {
        cout<<"WRONG";
        return 0;
    }

    F1.close();
    for(int i=1;i<6;i++){
            entrophyT.push_back(gettheoreticalentrophy(chances,i));
            entrophyP.push_back(getpracticalentrophy("F1.txt",sizeoffile,alphabet,i));
    }


    chances[0]=0.1;
    chances[1]=0.2;
    chances[2]=0.3;
    chances[3]=0.4;

    if(genfile(F1,alphabet,chances,sizeoffile)!=errcode::GOOD)
    {
        cout<<"WRONG";
        return 0;
    }

    for(int i=1;i<6;i++){
    entrophyT.push_back(gettheoreticalentrophy(chances,i));
    entrophyP.push_back(getpracticalentrophy("F2.txt",sizeoffile,alphabet,i));
    }

    cout<<"ravnomernoe:\n\nelement  Hteor  Hpractic\n";
    for(int i=0;i<5;i++)cout<<i+1<<"        "<<
        entrophyT[i]<<"      "<<entrophyP[i]<<endl;

    cout<<"\n\nbernulli:\n\nelement  Hteor   Hpractic\n";
    for(int i=5;i<10;i++)cout<<i-4<<"        "<<
        entrophyT[i]<<" "<<entrophyP[i]<<endl;
}
