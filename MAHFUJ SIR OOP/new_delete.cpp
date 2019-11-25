/** C++ uses new operator for dynamically allocating memory (C uses malloc()). */
/** Automatically allocate enough memory, no need of sizeof(). */
/** General form of initializing dynamic memory:
                        p-var = new type (initial value);

General form of allocating 1D array:
                        p-var = new type [size]; */

/** C++ uses delete operator for releasing dynamically allocating memory ,
(C uses free()).

The general form of delete operator:  delete p-var;
General form of releasing dynamically allocated array: delete [] p-var; */


#include<bits/stdc++.h>
using namespace std;

class samp
{
    int i, j;
public:
    samp(){cout<<"Constructing .....in samp..\n";}
    samp(int a, int b){i = a;j = b;}
    void setx(int a,int b){i=a,j=b;}
    int get_product(){return i*j;}
};

class myclass
{
    int i, j;
public:
    myclass(){cout<<"Constructor.......\n";}
    myclass(int a,int b){i=a,j=b;}
    void setx(int a,int b){i=a,j=b;}
    int get_product(){return i*j;}

};

int main()
{
    samp *p;
    p = new samp(4,5);

    cout<<p->get_product()<<endl;; /** It works ; */
    delete p;

    cout<<p->get_product()<<endl; /** garbage */

     myclass *q = new myclass[4];


    for(int i=0 ; i<4 ; i++){ p[i].setx(i,i+1); q[i].setx(i*i,i+1) ;}

    for(int i=0 ; i<4 ; i++)
    {
        cout<<"p["<<i<<"] "<<p[i].get_product()<<"      "<<"q["<<i<<"] "<<q[i].get_product()<<endl;
    }



    /** for(int i=0 ; i<4 ; i++,p++,q++){ p->setx(i*i,i+1); q->setx(i*i,i+1) ;}

    for(int i=0 ; i<4 ; i++,p++,q++)
    {
        cout<<"p->"<<i<<" "<<p->get_product()<<"      "<<"q->"<<i<<" "<<q->get_product()<<endl;

    }not allowed........... */

    cout<<"####### line 70\n" ; samp *ob ; ob = new samp[4];

    for(int i=0 ; i<4 ; i++)ob[i].setx(i,i*5);

    for(int i=0 ; i<4 ; cout<<ob[i++].get_product()<<" ");





    return 0;
}
