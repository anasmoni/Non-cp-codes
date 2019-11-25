#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;

class base
{
    int x ;
public:
    void setx(int n){x=n ;}
    void showx(){cout<<x<<endl ;}
    int getx(){return x;}
};

class derived:public base /** derived class can access only the public members of base class directly */
{
    int y;
public:
    void sety(int n){y=n ;}
    void showx_plus_y(){cout<<getx()+y<<endl ;}
    int gety(){return y;}
};


int main()
{
    derived ob;

    ob.setx(3);
    ob.sety(4);
    ob.showx();
    ob.showx_plus_y();
    base b;
    b=ob;
    b.showx();
//    ob=b; error

    return 0 ;
}

