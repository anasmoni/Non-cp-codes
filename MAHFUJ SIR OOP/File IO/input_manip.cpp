#include<bits/stdc++.h>
using namespace std;

istream &getpass(istream &stream){
    cout<<'\a';
    cout<<"Enter password : ";
    return stream;
}


int main()
{
    string pass;
    while(pass!="exit"){
        cin>>getpass>>pass;
    }

    return 0;
}
