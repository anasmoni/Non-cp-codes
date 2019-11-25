#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
    int n,n1,n2;
    scanf("%d%d%d",&n,&n1,&n2);

    for(int i=0 ; i<n ; i++){
        scanf("%d",&a[i]);
    }
    sort(a,a+n);
     float N1=0,N2=0;
    int mn = min(n1,n2); int MN=mn;
    n1 = max(n1,n2); int N=n1;
    for(int i=n-1 ;i>=0 ; i--){
        if(MN){N2+=a[i];MN--;}
        else if(N && !MN){N1+=a[i];N--;}
        else break;
    }

    printf("%0.8f",N1/n1 + N2/mn);



    return 0;
}
