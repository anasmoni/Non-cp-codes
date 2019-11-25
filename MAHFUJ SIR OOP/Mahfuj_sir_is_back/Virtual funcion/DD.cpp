#include<bits/stdc++.h>
using namespace std;

int p(int n){
    if(n<=1)return 0;
    else{
        for(int i=2 ; i*i<=n ; i++){
            if(n%i==0)return 0;
        }
        return 1;
    }
}

int main()
{
    int n;scanf("%d",&n);
    if(p(n)){cout<<"1";return 0;}

    if((n%2==0 && p(n/2)) || p(n-2))cout<<"2";
    else{
        for(int i=3 ; i<=n/2 ; i+=2){
            if(p(i) && p(n-i)){cout<<"2";return 0;}
        }
        cout<<"3";
    }

    return 0;
}
