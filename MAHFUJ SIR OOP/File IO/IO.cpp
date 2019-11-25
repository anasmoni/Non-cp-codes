#include<bits/stdc++.h>

using namespace std;

int main()
{
    cout.unsetf(ios::dec); // not required for all compilars......turns off the decimal flag
    cout.setf(ios::hex | ios::scientific);
    cout<<1254<<" "<<"hello "<<" "<<11.240<<endl;

    //cout.unsetf(ios::hex | ios::scientific);

    cout.setf(ios::showpos); // not for fraction
    int n=-10;
    cout<<"line 15 -> "<<100<<" "<<n<<endl;;

    cout.unsetf(ios::showpos | ios::fixed);

    cout<<"line 19 -> "<<45<<" "<<4.5448<<" "<<-10<<endl;

    cout.setf(ios::showpoint | ios::fixed);  // without setting fix 23 line will print sceintific as scientific didn't unset

    cout<<100.07<<endl;

    cout.unsetf(ios::showpoint | ios::fixed); // without unsetting fix...line 27 print 1.42;

    cout<<1.42<<endl;



    return 0;
}
