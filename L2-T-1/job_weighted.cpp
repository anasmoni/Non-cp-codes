#include<bits/stdc++.h>
using namespace std;
/**https://youtu.be/cr6Ip0J9izc**/

struct job
{
    int s,e,w;
    job(int ss, int ee ,int ww)
    {
        s=ss;
        e=ee;
        w=ww;
    }
};

bool operator<(job A , job B)
{
    return A.e<B.e;   // use <
}

int profit(vector<job> &v , int a[] , int sz)
{

    int mx = INT_MIN;

    for(int j=0 ,i=1 ; i<sz  ; )
    {

        if( v[i].s >= v[j].e )
        {

            a[i] = max(v[i].w + a[j] , a[i]) ;
            j++;
        }
        else i++,j=0;

        if(j==i) j=0 , i++;
    }

    for(int i=0 ; i<sz ; i++) mx = max(a[i],mx);


    return mx;
}

int main()
{
    int t;
    cin>>t;

    while(t--)
    {
        vector<job>v;

        int m;
        cin>>m;
        int a[m];

        for(int i=0 ; i<m ; i++)
        {

            int s,e,w;
            cin>>s>>e>>w;
            v.push_back(job(s,e,w));
        }

        sort(v.begin(), v.end());

        for(int i=0 ; i<m ; i++ )a[i]=v[i].w;

        cout<<profit(v,a,m)<<endl;
    }
    return 0;
}

/**
job arr[] = {{1, 2 ,3},{3 ,4 ,4}};

bool fun(job A , job B) return A.e<B.e;

sort(arr,arr+m,fun);

**/
