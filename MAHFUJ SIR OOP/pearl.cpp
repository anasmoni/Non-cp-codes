#include<bits/stdc++.h>
#include<set>

using namespace std;

int main()
{
    int n,m=0 ;
    scanf("%d",&n);
    int a[n];

    for(int i=0 ; i<n ; i++)scanf("%d",&a[i]);

    set<int>s(a,a+n);
    multiset<int>ms(a,a+n);

    if(n==s.size())
    {
        cout<<"-1";
        return 0 ;
    }

    set<int>::iterator it;

    it = s.begin() ;
    m=0;
    int mx;
    while(it!=s.end())
    {
        if(ms.count(*it)>m)m=ms.count(*it) , mx=*it;
        it++;
    }

    cout<<m/2<<endl;
    it=s.begin();

    while(it!=s.end())
    {
        for(int i=0,j=0 ; i<n ; i++)
        {
            if(*it==a[i] && a[i]==mx)
            {
                cout<<i+1<<" ";
                j++;
                if(!(j%2))cout<<endl;
            }
        }
        it++;
    }


    return 0;
}
