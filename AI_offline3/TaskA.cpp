#include<bits/stdc++.h>
using namespace std;

typedef long long int lli;
typedef unsigned long long int ulli;
typedef pair<int,int> pii;

#define ones(x) __builtin_popcount(x)
#define onesl(x) __builtin_popcountl(x)
#define onesll(x) __builtin_popcountll(x)

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define scn(n) scanf("%d",&n)
#define scnll(n) scanf("%lld",&n)
#define scn2(n,m) scanf("%d%d",&n,&m)
#define scn3(n,m,w) scanf("%d%d%d",&n,&m,&w)
#define scn2ll(n,m) scanf("%lld%lld",&n,&m)
#define atoz(v) v.begin(),v.end()
#define ratoz(v) v.rbegin(),v.rend()
#define Fill(a,v) memset(a,v,sizeof(a))
#define sz(v) v.size()
#define fi first
#define se second
#define inf 1e9
#define pi acos(-1.0)
#define sqr(x) x*x
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define ten(n) (int)1e##n
#define tenll(n) (lli)1e##n
#define mod 1000000007
#define FastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int Set(int N,int pos)
{
    return N=N | (1<<pos);
}
int reset(int N,int pos)
{
    return N = N & ~(1<<pos);
}
bool check(int N,int pos)
{
    return (bool)(N & (1<<pos));
}

///priority_queue< int, vector< int >, greater< int > > minHeap;
bool g(string a , string b){

    if(a.size()<b.size()) return true;
    if(a.size()>b.size()) return false;

    for(int i=0; i<a.size(); i++){
        if(a[i]<b[i])return true;
    }
    return false;
}

int main()
{
    ///freopen("output.txt","w",stdout);
    ///freopen("input.txt","r",stdin);

    ///FastIO;

    int t;
    scn(t);

    while(t--){
        lli n,k;
        scn2ll(n,k);
        cout<<(9*(n-1) + k);

    }


    return 0;
    ///return main();
}

///sin and cos expect input in radians not degrees. so use , sin(degrees * pi / 180)
