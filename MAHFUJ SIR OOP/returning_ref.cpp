#include<bits/stdc++.h>
using namespace std;

int y;

int &f(){int x ; return x;}

int &F(){return y;}

int main()
{
    f() = 100;
    F() = 14;
    cout<<f()<<endl<<F()<<endl<<y<<endl;

    /** independent reference */

    int b=45;
    int &r = b;
    cout<<b<<endl<<r<<endl;
    /** &r = 10;  error*/
    r=78; int m=r;
    cout<<b<<endl<<r<<endl<<m;

    return 0;
}
