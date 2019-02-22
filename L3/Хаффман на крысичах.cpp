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
#include "entrophy.h"
using namespace std;

///////////////
struct versh
{
    float chance;
    unsigned char symbol;
    float accamulationchance;
    int lengthcode;
    char code[100];
};
struct versh2
{
    unsigned char symbol;
    char code[100];
};
void quicksortchance(versh *A,int l,int r)
{
    int i,j;
    float t,x;
    unsigned char t1;
    x=A[(l+r)/2].chance;
    i=l;
    j=r;
    while (i<=j)
    {
        while(A[i].chance>x)
        {
            i++;
        }
        while(A[j].chance<x)
        {
            j--;
        }
        if(i<=j)
        {
            t=A[i].chance;
            t1=A[i].symbol;
            A[i].chance=A[j].chance;
            A[i].symbol=A[j].symbol;
            A[j].chance=t;
            A[j].symbol=t1;
            i++;
            j--;
        }
    }
    if(l<j)
    {
        quicksortchance(A, l, j);
    }
    if(i<r)
    {
        quicksortchance(A, i, r);
    }
}
float razmer(const char *namefile)
{
    FILE *f = fopen(namefile,"r");
    float size=0;
    fseek(f,0,2);
    size=ftell(f);
    return size;


}
void initialization(versh *Q1)
{
    for(int i=0; i<255; i++)
    {
        Q1[i].chance=0;
        Q1[i].accamulationchance=0;
        Q1[i].lengthcode=0;
    }
}

void zapolnit(float &s,FILE *ptr,versh *Q1,unsigned char &temp,int &n)
{

    while(!feof(ptr))
    {
        temp=getc(ptr);
        if(feof(ptr))
            break;
        Q1[int(temp)].chance++;
    }

    for(int i=0; i<255; i++)
        s=s+Q1[i].chance;
    for(int i=0; i<255; i++)
        Q1[i].chance=Q1[i].chance/s;
    s=0;
    //float temps;
    //for(int i=0;i<255;i++)temps=temps+Q1[i].chance;
    //printf("%f",temps);
    //system("pause");
    for(int i=0; i<255; i++)
    {
        Q1[i].symbol=(i);
    }
    quicksortchance(Q1,0,254);
    for(int j=0; j<255; j++)
    {
        for(int i=0; i<=j; i++)
        {
            Q1[j].accamulationchance=Q1[j].accamulationchance+Q1[i].chance;
        }
    }
    for(int i=0; i<255; i++)
    {
        if(Q1[i].chance)
            n++;
    }
    n++;
    for(int i=0; i<255; i++)
        s=s+Q1[i].chance;


    // for(int i=0;i<n-1;i++){Q1[i].lengthcode=(log(Q1[i].chance)/log(0.5))+1;}
}
/////

/////////////////////
void indexmas(versh *Q1,versh2 *Q2,char *ttt,int C[][500],int n)
{
    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j<Q1[i].lengthcode; j++)
        {
            if(C[i][j])
                ttt[j]='1';
            else
                ttt[j]='0';

        }
        ttt[Q1[i].lengthcode]='\0';
        strcpy(Q1[i].code,ttt);
        //cout<<Q1[i].code<<"\n";
    }

    //for (int i=0;i<n-1;i++){cout<<Q1[i].symbol<<Q1[i].code<<"\n";}


    for(int i=0; i<n-1; i++)
    {
        Q2[Q1[i].symbol].symbol=Q1[i].symbol;
        strcpy(Q2[Q1[i].symbol].code,Q1[i].code);
    }
}
//////////

void sjatief(FILE *ptr1,FILE *ptr5,versh2 *Q2,long int &kol,unsigned char &temp,int &dvo,int &i,char *buffer,char *buf)
{



    while(!feof(ptr1))
    {

        temp=getc(ptr1);
        if (feof(ptr1))
            break;

        strcat(buffer,Q2[temp].code);

        while(strlen(buffer)>7)
        {
            i=strlen(buffer);
            i=i-1;
            if (i<7)
                continue;
            else
            {
                strncpy(buf,buffer,8);
                buf[8]='\0';

                for(int rer=0; rer<8; rer++)
                {
                    dvo=dvo+(buf[7-rer]-'0')*(pow(2,rer));
                }

                if (dvo==10)
                {
                    putc(dvo,ptr5);
                }
                else

                    putc(dvo,ptr5);
                kol++;
                dvo=0;
                for(int z=8; z<=strlen(buffer); z++)
                {
                    buffer[z-8]=buffer[z];
                }
            }
        }
    }
    int ostatok=strlen(buffer);
    int inc=0;


    for (int i=ostatok-1; i>=0; i--)
    {
        buffer[7-i]=buffer[inc];
        inc++;
    }
    for (int i=0; i<8-ostatok; i++)
    {
        buffer[i]='0';
    }
    //for (int i=0;i<8-ostatok;i++){buffer[i]=0;}
    buffer[8]='\0';

    dvo=0;
    strncpy(buf,buffer,8);
    buf[8]='\0';
    for(int rer=0; rer<8; rer++)
    {
        dvo=dvo+(buf[7-rer]-'0')*(pow(2,rer));
    }
    kol++;
    putc(dvo,ptr5);
}

void razjatie(FILE *ptr4,FILE *ptr6,long int &kol,versh *Q1,versh2 *Q2,int &n,unsigned char &temp1,char* buffir,char *vrem)
{

    while(kol)
    {
        temp1=getc(ptr4);
        kol--;

        int x=int(temp1);
        int testx=x;
        char res[100];
        int u=0;
        for(int i=0; i<8; i++)
            res[i]='0';
        for( ; x; x/=2)
        {
            res[7-u]=(unsigned char)(x%2+'0');
            u++;
        }
        res[8]='\0';
        strcat(buffir,res);
        ///////////

        int found=1;
        int kiiu=0;
        while(strlen(buffir)>15)
            while(found)
            {
                kiiu++;
                strncpy(vrem,buffir,kiiu);
                vrem[kiiu]='\0';


                for (int i=0; i<n-1; i++)
                {
                    if(strcmp(vrem,Q2[Q1[i].symbol].code)==0)

                    {
                        //cout<<char(Q2[Q1[i].symbol].symbol)<<" "<<kl<<" "<<buffir<<" "<<res<<"    "<<Q2[Q1[i].symbol].code<<"\n";
                        putc(Q2[Q1[i].symbol].symbol,ptr6);
                        //cout<<buffir<<" "<<kiiu<<" "<<vrem<<"\n";//system("pause");
                        //cout<<buffir<<"\n";
                        //cout<<strlen(buffir)<<"\n";

                        for(int z=kiiu; z<=strlen(buffir); z++)
                        {
                            buffir[z-kiiu]=buffir[z];
                        }

                        kiiu=0;
                        break;
                    }
                }

                if (kiiu==strlen(buffir))
                {
                    kiiu=0;
                    break;
                }
            }
    }

}
void   parametrs(versh *Q1,int &n)
{
    float srdlin=0;
    for(int i=0; i<n-1; i++)
    {
        srdlin+=Q1[i].lengthcode*Q1[i].chance;
    }
    printf("sred dlina coda:%f\n",srdlin);
    float entrop=0;
    for(int i=0; i<n-1; i++)
    {
        entrop=entrop-Q1[i].chance*log(Q1[i].chance)/log(2);
    }
    printf("entropiia:%f\n",entrop);
    float izbyto4nost=0;
    izbyto4nost=srdlin-entrop;
    printf("izbytochnost:%f\n",izbyto4nost);
    float raz,dva,sjatie;
    raz=razmer("RUS.txt");
    dva=razmer("outhuf.txt");
    cout<<dva<<" "<<raz;
    sjatie=dva/raz;
    printf("sjatie:%f",sjatie);
    system("pause");
    system("cls");
}
///////////////////////////////////
int up(int n, float q,versh *Q1)
{
    int i;
    for (i = n - 2; i >= 1; i--)
    {
        if (Q1[i - 1].chance <= q)
        {
            Q1[i].chance = Q1[i - 1].chance;
        }
        else
        {
            break;
        }
    }
    Q1[i].chance = q;
    return i;
}
//-------------------------------
int down(int n, int j,int c[][500],versh *Q1)
{
    int i, z, l1;
    int s[16];

    for (z = 0; z < 16; z++)
    {
        s[z] = c[j][z];
    }
    l1 = Q1[j].lengthcode;
    for (i = j; i <= n - 2; i++)
    {
        for (z = 0; z < 16; z++)
        {
            c[i][z] = c[i + 1][z];
        }
        Q1[i].lengthcode = Q1[i+1].lengthcode;
    }
    for (z = 0; z < 16; z++)
    {
        c[n - 1][z] = s[z];
        c[n][z] = s[z];
    }
    c[n - 1][l1] = 0;
    c[n][l1] = 1;
    Q1[n-1].lengthcode = l1 + 1;
    Q1[n].lengthcode = l1 + 1;

    return 0;
}
//-------------------------------
int huffman(int n,versh *Q1,int c[][500])
{
    float q;
    int j;
    if (n == 1)
    {
        c[0][0] = 0;
        Q1[0].lengthcode = 1;
        c[1][0] = 1;
        Q1[1].lengthcode = 1;
    }
    else
    {
        q = Q1[n-1].chance + Q1[n].chance;
        j = up(n, q,Q1);
        huffman(n - 1,Q1,c);
        down(n, j,c,Q1);
    }
    return 0;
}
//////////////////////////////
int main()
{
    printf("");
    versh Q1[256];
    versh2 Q2[256];
    int n=0;
    int C[256][500];
    char ttt[100];

    unsigned char temp;
    initialization(Q1);
    FILE *ptr;
    float s=0;
    ptr=fopen("RUS.txt","r");


    zapolnit(s,ptr,Q1,temp,n);
    //codeandindexmas(C,n,Q1,Q2,ttt);
    versh Q1temp[n-1];
    for (int li=0; li<n-1; li++)
    {
        Q1temp[li].chance=Q1[li].chance;
    }

    //Fano(C,L,R,Q1,k);
    huffman(n-2,Q1,C);
    int lel=0;
    //for(int i=0;i<n;i++){lel++;cout<<lel<<")"<<Q1[i].lengthcode<<" "<<Q1[i].symbol<<" "<<Q1[i].accamulationchance<<"   "<<Q1[i].chance<<"\n";}

    indexmas(Q1,Q2,ttt,C,n);
    // for(int kek=0;kek<n-1;kek++) cout<<char(Q2[Q1[kek].symbol].symbol)<<"    "<<Q2[Q1[kek].symbol].code<<"\n";
    system("pause");
    fclose(ptr);
    FILE *ptr1;
    FILE *ptr5;
    long int kol=0;
    char buffer[100];
    char buf[100];
    int dvo;
    int i=0;
    ptr5=fopen("outhuf.txt","wb");
    ptr1=fopen("RUS.txt","rb");
    sjatief(ptr1,ptr5,Q2,kol,temp,dvo,i,buffer,buf);
    fclose(ptr1);
    fclose(ptr5);
    cout << endl;
    for (int li=0; li<n-1; li++)
    {
        Q1[li].chance=Q1temp[li].chance;
    }

    parametrs(Q1,n);
    FILE *ptr4,*ptr6;
    ptr4=fopen("outhuf.txt","rb");
    ptr6=fopen("refacthuf.txt","wb");
    unsigned char temp1;
    char buffir[100];
    char vrem[1000];
    razjatie(ptr4,ptr6,kol,Q1,Q2,n,temp1,buffir,vrem);
    fclose(ptr4);
    putc(255,ptr6);
    fclose(ptr6);

    system("pause");
    //////////////////////////////////////
    cout<<"OVERALL TABLE:\n";
    cout<<"RUS text H:\n\n";
    for(int i=1; i<4; i++)
    {
        cout<<entrophy("RUS.txt",i)<<" ";
    }
    cout<<"\n\nHuffman coded the same text H\n\n";
    for(int i=1; i<4; i++)
    {
        cout<<entrophy("outhuf.txt",i)<<" ";
    }
}



