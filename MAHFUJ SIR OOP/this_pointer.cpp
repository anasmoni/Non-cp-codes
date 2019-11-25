#include<bits/stdc++.h>
using namespace std;

class myclass
{
    int n;
    double d;
    char s[40];
public:
    myclass(int N,double D,char S[])
    {
        this->d=D;
        this->n=N;
        strcpy(this->s,S);
    }
    int get(){return n;}
    double getd(){return d;}

};


int main()
{
    myclass ob(2,3.4,"Hello World!");

    cout<<ob.get()<<endl<<ob.getd()<<endl;

    return 0;
}
