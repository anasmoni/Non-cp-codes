#include<bits/stdc++.h>
using namespace std;

int parti(int a[] , int lo , int hi)
{
    int i=lo , piv = a[hi];
    for(int j=lo ; j<hi ; ++j)
    {
        if(piv>=a[j])
        {
            swap(a[i],a[j]);
            ++i;
        }
    }
    swap(a[hi],a[i]);
    return i;
}

void qs(int a[] , int lo , int hi)
{
    if(lo<hi)
    {
        int idx = parti(a , lo , hi);
        qs(a,lo,idx-1);
        qs(a,idx+1,hi);
    }
}

int main()
{

    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int a[n];

        for(int i=0 ; i<n ; cin>>a[i++]);
        qs(a,0,n-1);
        for(int i=0 ; i<n ; cout<<a[i++]<<" ");
        cout<<endl;
    }

    return 0;
}
