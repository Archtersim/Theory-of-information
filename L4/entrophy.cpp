#include "entrophy.h"

unsigned char torus(unsigned char c)
{
    if(c>191&&c<224)
        c+=32;
    if(c==','||c=='?'||c=='!'||c=='-'||c==':'||c=='"'||c=='\'')
        c='.';
    if(c==' ')
        c='_';
    if(c=='¨')
        c='¸';
    return c;
}

void initnewalphabet(vector <unsigned char>alphabet,vector <string>& newalphabet,map <string,int> &hz,int dim,int &newrealsize)
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
        alphabet.clear();
        alphabet.shrink_to_fit();
    return;
};


double getpracticalentrophy(string fname,vector<unsigned char> alphabet,int dim,int modeRUS)
{
    ifstream F1;
    unsigned char c[1];
    map <string,int>hz;
    unsigned char word[dim];
    int newrealsize=0;
    vector <string> newalphabet;
    initnewalphabet(alphabet,newalphabet,hz,dim,newrealsize);

    int realsize=0;
    F1.open(fname,ios::binary);

    vector<string> dictionary;
    if(!F1.read((char *)(&word),dim))
        return -4;

    if(modeRUS)
    {
        for(int i=0; i<dim; i++)
        {
            word[i]=torus(word[i]);
        }
    }

    while(F1.read((char*)(&c),1))
    {
        if(modeRUS)
            c[0]=torus(c[0]);
        string s;
        for(int i=0; i<dim; i++)
            s.push_back(word[i]);
        hz[s]++;
        realsize++;
        dictionary.push_back(s);
        for(int i=1; i<dim; i++)
            word[i-1]=word[i];
        word[dim-1]=c[0];

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

        if(p>0)
            res=res-log2(p)*p;

    }
    dictionary.clear();
dictionary.shrink_to_fit();
st.clear();
hz.clear();
newalphabet.clear();
newalphabet.shrink_to_fit();

    return res/(double)dim;
}

double entrophy(string fname,int dim)
{
    setlocale(0,"");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    vector<unsigned char> alphabet256;
    vector <double> entrophyP;
    ifstream F1;
    F1.open(fname,ios::binary);
    unsigned char c[1];
    while(F1.read((char*)(&c),1))
    {

        if(std::find(alphabet256.begin(), alphabet256.end(), c[0]) == alphabet256.end())
        {
            alphabet256.push_back(c[0]);
        }
    }
    F1.close();
    entrophyP.clear();
    entrophyP.shrink_to_fit();
    return getpracticalentrophy(fname,alphabet256,dim,0);
}


