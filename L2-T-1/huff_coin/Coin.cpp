#include<bits/stdc++.h>
using namespace std;

int temp[100005],num[100005] , res[100005];

void mergesort(int lo , int hi )
{
    if(lo==hi)return;

    int mid = (lo+hi)/2 ;

    mergesort(lo,mid);
    mergesort(mid+1,hi);

    int i,j,k;
    //cout<<lo<<" "<<hi<<endl;
    for(i=lo , j=mid+1,k=lo ; k<=hi ; k++)
    {
        if(i==mid+1)temp[k]=num[j++];
        else if(j==hi+1)temp[k]=num[i++];
        else if(num[i]<num[j])temp[k]=num[i++];
        else temp[k]=num[j++];
    }

    for(k=lo ; k<=hi ; k++)num[k]=temp[k];
//    for(k=lo ; k<=hi ;cout<<num[k++]<<" ");cout<<endl;
}

void solve(int n , int w){

    memset(res,0,sizeof(res));
    int tot=0;

    for(int i=n ; i>=1&&w>0 ; i--)
    {
        while(w>=num[i] && num[i]>0){
            w-=num[i];
            res[num[i]]++;
        }
        tot+=res[num[i]];
    }
    if(w){
        cout<<"Impossible for Greedy.....\n";
        return;
    }
    cout<<tot<<endl;

    for(int i=n ; i>=1  ; i--){
        if(res[num[i]])printf("%d %d\n",num[i],res[num[i]]);
    }

}

int main()
{

    while(true){
        cout<<"Enter 0 to exit.....\n";
        int n,w;
        scanf("%d",&n);
        //memset(temp,0,sizeof(temp));
        //memset(num,0,sizeof(num));
        if(!n)break;

        for(int i=1; i<=n ; scanf("%d",&num[i++]));
        scanf("%d",&w);

        mergesort(1,n);

        solve(n,w);



    }

    return 0;
}
