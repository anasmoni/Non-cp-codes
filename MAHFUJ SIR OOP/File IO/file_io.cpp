#include<bits/stdc++.h>
using namespace std;

int main()
{
    ofstream ofs("test");

    if(!ofs){cout<<"Null";return 1;}

    ofs<<"Hello\n"<<100<<" "<<hex<<100;
    ofs.close();// run without it
    ifstream ifs("test");

    if(!ifs){cout<<"Can't open"; return 0;}

    string s; int i,j;
    ifs>>s>>i>>j;
    cout<<s<<endl<<i<<endl<<j;

    return 0;
}
