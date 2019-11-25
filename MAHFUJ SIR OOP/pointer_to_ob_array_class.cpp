#include<bits/stdc++.h>
using namespace std;

class myclass
{
    int n;
public:
    myclass(int m){n=m;}
    int getn(){return n;}
    myclass(int i,int j){n = i+j ;}
};


int main()
{
    myclass obj[4] = {myclass(8,9),myclass(2,3),myclass(3,2),myclass(4,5)}; /** for multiple parameter */

    myclass *p;
    p=obj ;

    for(int i=0 ; i<4 ; i++)cout<<p++->getn()<<endl;

    return 0;
}
