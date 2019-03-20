#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include <fstream>
#include <math.h>
#include <locale.h>
#include <windows.h>
using namespace std;

///////////////
struct versh
{
    float chance;
    string symbol;
    float accamulationchance;
    int lengthcode;
    string code;
};
struct versh2
{
    int numofsymbol;
    string code;
};


float razmer(const char *namefile)
{
    FILE *f = fopen(namefile,"r");
    float size=0;
    fseek(f,0,2);
    size=ftell(f);
    return size;
}
void initialization(versh *Q1,int lengthofblock)
{
    for(int i=0; i<1024; i++)
    {
        Q1[i].chance=1;
        Q1[i].accamulationchance=0;
        Q1[i].lengthcode=0;
    }
}

void zapolnit(float &s,versh *Q1,unsigned char &temp,int &n,int lengthofblocks,double p0,double p1)
{
    int blockbinview=0;
    for(int j=0; j<pow(2,lengthofblocks); j++)
    {
        int e=blockbinview;
        int i=0;
        string s(lengthofblocks,'0');
        Q1[j].symbol=s;
        while(e!=0)
        {
            Q1[j].symbol[lengthofblocks-i-1]=(e%2==0 ?'0':'1');
            e/=2;
            i++;
        }

        blockbinview++;
    }

    for(int j=0; j<pow(2,lengthofblocks); j++)
    {
        for(int i=0; i<lengthofblocks; i++)
        {
            if(Q1[j].symbol[i]=='0')
                Q1[j].chance*=p0;
            else
                Q1[j].chance*=p1;


        }
    }
    for(int j=0; j<pow(2,lengthofblocks); j++)
    {

        for(int i=0; i<j; i++)
        {
            Q1[j].accamulationchance=Q1[j].accamulationchance+Q1[i].chance;
        }
        Q1[j].accamulationchance=Q1[j].accamulationchance+Q1[j].chance/2;
    }
    for(int i=0; i<pow(2,lengthofblocks); i++)
    {
        if(Q1[i].chance)
            n++;
    }
    for(int i=0; i<pow(2,lengthofblocks); i++)
        s=s+Q1[i].chance;
    versh tmp[1024];

    int z=0;

    //cout<<z<<endl;
    for(int i=0; i<n; i++)
    {
        if(Q1[i].chance)
            Q1[i].lengthcode=(log(Q1[i].chance)/log(0.5))+2;
    }
    int lel=0;
    for(int i=0; i<n; i++)
    {
        lel++;
        //cout<<lel<<")"<<Q1[i].lengthcode<<" "<<Q1[i].symbol<<" "<<Q1[i].accamulationchance<<"   "<<Q1[i].chance<<"\n";
    }
}
/////
void codeandindexmas(int C[][100],int &n,versh *Q1,versh2 *Q2,char *ttt,int lengthofblock)
{


    for (int i=0; i<n; i++)
    {
        for (int j=0; j<100; j++)
        {
            C[i][j]=9;
        }
    }


    for (int i=0; i<n; i++)
    {
        for (int j=0; j<Q1[i].lengthcode; j++)
        {
            Q1[i].accamulationchance=Q1[i].accamulationchance*2;

            C[i][j]=Q1[i].accamulationchance;
            if(C[i][j]==2)
                C[i][j]=0;
            if(Q1[i].accamulationchance>1)
            {
                Q1[i].accamulationchance=Q1[i].accamulationchance-1;
            }
        }
    }


    for (int i=0; i<n; i++)
    {
        for (int j=0; j<Q1[i].lengthcode; j++)
        {
            if(C[i][j])
                ttt[j]='1';
            else
                ttt[j]='0';

        }
        ttt[Q1[i].lengthcode]='\0';
        string s(ttt);
        Q1[i].code=s;
    }

    for (int i=0; i<n; i++)
    {
        // cout<<Q1[i].symbol<<Q1[i].code<<"\n";
    }


    for(int i=0; i<n; i++)
    {
        string s(Q1[i].symbol);
        int numofblock=stoi(s, nullptr, 2);

        Q2[numofblock].numofsymbol=numofblock;
        Q2[numofblock].code=Q1[i].code;
        //cout<<Q2[numofblock].code<<endl;
    }

}

//////////


void   parametrs(versh *Q1,int &n,int sizeofblock)
{
    cout<<"size of block: "<<sizeofblock<<endl;
    float srdlin=0;
    for(int i=0; i<n; i++)
        srdlin+=Q1[i].lengthcode*Q1[i].chance;
    printf("sred dlina coda na 1 byte:%f\n",srdlin/(float)sizeofblock);
    float entrop=0;
    for(int i=0; i<n; i++)
    {
        //cout<<Q1[i].chance<<endl;
        entrop=entrop-Q1[i].chance*log(Q1[i].chance)/log(2);
    }
    printf("entropiia na 1 byte:%f\n",entrop/(float)sizeofblock);
    float izbyto4nost=0;
    izbyto4nost=srdlin-entrop;
    printf("izbytochnost na 1 byte:%f\n",izbyto4nost/(float)sizeofblock);

    system("pause");
    system("cls");
}

int main()
{
    printf("");
    setlocale(0,"");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    for(int sizeofblock=1; sizeofblock<11; sizeofblock++)
    {

        versh Q1[1024];
        versh2 Q2[1024];
        int n=0;
        int C[1024][100];
        char ttt[100];

        unsigned char temp;
        initialization(Q1,sizeofblock);
        FILE *ptr;
        float s=0;

        double p0=0.4,p1=0.6;
        zapolnit(s,Q1,temp,n,sizeofblock,p0,p1);
        int lel=0;
        for(int i=0; i<n; i++)
        {
            lel++;
             cout<<lel<<")"<<Q1[i].lengthcode<<" "<<Q1[i].symbol<<" "<<Q1[i].accamulationchance<<"   "<<Q1[i].chance<<"\n";
        }

        //system("pause");
        codeandindexmas(C,n,Q1,Q2,ttt,sizeofblock);
        parametrs(Q1,n,sizeofblock);
    }


    system("pause");
    //////////////////////////////////////
}



