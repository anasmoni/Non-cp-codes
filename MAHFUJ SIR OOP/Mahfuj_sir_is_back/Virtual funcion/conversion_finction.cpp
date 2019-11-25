#include<bits/stdc++.h>
using namespace std;

class coord{
    int x,y;
public:
    coord(int i,int j){x=i;y=j;}
    operator int(){return x*y;}
    operator char(){return (char)x;}
};

int main()
{
    coord cd(5,4);
    cout<<(int)cd;
    int b = 100 + cd;
    cout<<endl<<b;
    cout<<endl<<(char)cd+100;
    char c = cd+'a';
    cout<<endl<<c;
    return 0;
}
