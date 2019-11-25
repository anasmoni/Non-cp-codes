#include<bits/stdc++.h>
using namespace std;

class myclass{
    int n=5;
public:
    int getn(){return n;}
};

int main()
{
    vector<myclass>v;

    for(int i=0 ; i<10 ; i++){
        v.push_back(myclass());
    }

    for(int i=0 ; i<10 ; i++){
        cout<<v[i].getn()<<" ";
    }

    return 0;
}
