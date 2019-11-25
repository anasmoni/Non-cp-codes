#include<bits/stdc++.h>
using namespace std;

void fun(const int *p){
    int *x;
    x = const_cast<int*>(p);
    *x=100;
}

void change(int &p){
    p = 44;
}

int main()
{
    int p = 10;
    fun(&p);
    cout<<p<<endl;

    char *s = "This a test";

    p = reinterpret_cast<int>(s);
    cout<<p<<endl;
    change(p);
    cout<<p;

    p = static_cast<int>(2.05);
    cout<<endl<<p;

    return 0;
}
