#include<bits/stdc++.h>
using namespace std;

void f(int *n){*n=100;} /** using pointer , not reference in c */

void f1(int &n){n=100;n++;} /** using reference in c++ */

class samp
{
    int n;
public:
    samp(int i){n=i;}
    int getn(){return n;}
    ~samp(){cout<<"\nDestructing....\n";}
};

void f(samp &ob){cout<<ob.getn();}

/**When an object is passed to a function by reference, no copy is made and therefore its
destructor function is not called when the function returns*/

int main()
{
    int n;
    f(&n) ;
    cout<<n<<endl;
    f1(n);
    cout<<n<<endl;

    samp ob(1);

    f(ob);


    return 0;
}
