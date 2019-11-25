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
    myclass ob[4] = {6,7,8,-4}; /** as we use single parametrised constructor*/

    for(int i=0 ; i<4 ; i++)cout<<"ob["<<i<<"] "<<ob[i].getn()<<endl;

    myclass ob1[4] = {myclass(89),myclass(23),myclass(32),myclass(45)}; /** or */

    for(int i=0 ; i<4 ; i++)cout<<"ob1["<<i<<"] "<<ob1[i].getn()<<endl;

    myclass o[4][2] = {1, 2, 3, 4, 5, 6, 7, 8};

    cout<<"##### Line 26\n";
    for( int i= 0; i < 4; i++ , cout<<endl)
    {
        cout << o[i][0].getn() <<' ';
        cout << o[i][1].getn() <<' ';
    }

    myclass obj[4] = {myclass(8,9),myclass(2,3),myclass(3,2),myclass(4,5)}; /** for multiple parameter */

    for(int i=0 ; i<4 ; i++)cout<<"obj["<<i<<"] "<<obj[i].getn()<<endl;

    myclass *p ; p=obj ; cout<<"###### line  39\n";

    for(int i=0 ; i<4 ; i++)cout<<p++->getn()<<"  "; /** okkk*/

    while(1)return 0;
}

