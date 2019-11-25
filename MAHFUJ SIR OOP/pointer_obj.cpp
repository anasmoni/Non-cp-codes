#include<bits/stdc++.h>
using namespace std;

class myclass
{
    int a, b;
public:
    myclass(int i, int j){a = i;b = j;}
    int get_a(){return a;}
    int get_b(){return b;}
};


int main()
{
    myclass ob[4] = {myclass(1,2),myclass(14,24),myclass(4,6),myclass(5,2)} ;
    myclass *p; p = ob;

    for(int i=4 ; i ; i--,p++,cout<<endl)cout<<"a is : "<<p->get_a()<<" and b : "<<p->get_b();

    return 0;
}
