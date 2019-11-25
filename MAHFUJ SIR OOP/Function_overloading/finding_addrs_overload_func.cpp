#include<bits/stdc++.h>
using namespace std;

void fun(char c){
    cout<<c<<endl;
}

void fun(int i , char c){
    cout<<i<<" "<<c<<endl;
}

int main()
{
    void(*fp1)(char);
    void(*fp2)(int , char);

    fp1 = fun;
    fp2 = fun;

    fp1('f');
    fp2(90,'x');

    return 0;
}
