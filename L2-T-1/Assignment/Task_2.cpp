#include<bits/stdc++.h>
using namespace std;

int a[1000],n;

int Major(int lo , int hi)
{

    if(lo==hi)return a[lo];

    int mid = (lo+hi)/2;

    int left = Major(lo,mid);
    int right = Major(mid+1,hi);

    if(left==right)return left;

    int left_count=0 , right_count=0;

    for(int i=1 ; i<=n ; i++)left_count += a[i]==left;

    for(int i=1 ; i<=n ; i++)right_count += a[i]==right;

    if(left_count > mid - (hi-lo+1)%2)return left;
    else if(right_count > mid - (hi-lo+1)%2)return right;
    else return -1;


}

int on_major()
{

    int  temp,cnt=0;

    for (int i = 1; i <=n; i++)
    {
        if (!cnt)
        {
            temp = a[i];
            cnt = 1;
        }
        else
        {
            if (temp == a[i])cnt++;
            else cnt--;
        }
    }

    if (cnt == 0)return -1;

    cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (temp == a[i])cnt++;
    }
    return cnt > n/2 - (n%2) ? temp : -1;
}

int main()
{

    while(1)
    {
        cout<<"Enter 0 to exit...\n";
        cin>>n;
        if(!n)break;
        for(int i=1 ; i<=n ; cin>>a[i++]);

        cout<<Major(1,n)<<" "; //O(nlogn)
        cout<<on_major()<<endl;; // O(n)
    }
}
