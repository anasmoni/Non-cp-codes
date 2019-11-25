#include<bits/stdc++.h>
using namespace std;

void func(int a=0 , int b=0){
    cout<<a<<" "<<b<<endl;
}

 /** void func(int i=0 , int m)  Error
 void func(int m , int i=0) okk */

void Bee(int a , int b=0){
    cout<<a<<" "<<b<<endl;
}

void change(int &n){
    n = 54;
}

int main()
{
    func();
    func(4);
    func(17,54);
    Bee(4);
    Bee(5445,65);
    int n=0;
    change(n);
    cout<<n;
    return 0;
}
