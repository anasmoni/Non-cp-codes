#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin>>n;

    while(n--)
    {
        int x,sum=1; cin>>x;

        x = pow(2,x-1)*(pow(2,x)-1);
        //cout<<x;

        for(int i=2 ; i<=x/2 ; i++){ x%i ? sum=sum : sum+=i ;}

        sum==x ? cout<<"YES\n" : cout<<"NO\n" ;
    }

    return 0;
}
