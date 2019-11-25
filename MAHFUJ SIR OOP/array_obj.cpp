#include<bits/stdc++.h>
using namespace std;

class myclass
{
    int n;
public:
    void setn(int m){n=m;}/** look here constructor isn't used*/
    int getn(){return n;}
};

int main()
{
    myclass ob[4];

    for(int i=1 ; i<5 ; i++)ob[i-1].setn(i);

    for(int i=0 ; i<4 ; i++)cout<<"ob["<<i<<"] "<<ob[i].getn()<<endl;

    return 0;
}
