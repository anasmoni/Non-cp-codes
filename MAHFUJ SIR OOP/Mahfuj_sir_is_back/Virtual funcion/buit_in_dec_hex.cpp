#include<bits/stdc++.h>
using namespace std;

int main()
{
    stringstream ss;
    ss<< hex <<1112312;
    string res ( ss.str() );
    cout << res<<endl;


    int d;
    stringstream strs;
    strs  << res;
    strs >> hex >> d;

    cout << d<<endl;

    cout<< hex << 11<<endl;

    cout<< oct << 123;

    return 0;
}
