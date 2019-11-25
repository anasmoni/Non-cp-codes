#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;cin>>n;
    int a[2*n];
    map<int,int>mp;
    int table=0,mx=-1;
    for(int i=0 ; i<2*n; i++){
        scanf("%d",&a[i]);
        if(mp[a[i]]){
            table--;
            mp[a[i]]=0;
        }
        else{
            table++;mp[a[i]]=1;
        }
        mx = max(mx,table);
    }
    printf("%d",mx);

    return 0;
}
