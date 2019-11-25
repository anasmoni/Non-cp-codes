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

void mor(){cout<<"NO"; exit(0);}


int main()
{
    ///freopen("output.txt","w",stdout);
    ///freopen("input.txt","r",stdin);
    ofstream out;
    out.open("input.txt");
    ///FastIO;
    string s = "contestbutnotestbuetcsecontest";
    map<char,char>cnt;
    for(int i=0; i<s.size(); i++){
        int p = s[i]-'a';
        p = (p+11)%26;
        out<<((char)(p+'A'));
        cnt[s[i]]++;
    }
    out<<"\n\n";
    vector<pii>v;
    for(int i=0; i<26; i++){
        char c = (char)(i+'a');
        if(cnt[c]) v.pb({cnt[c],i});
    }
    sort(atoz(v));

    while(v.size()){
        pii p = v.back();
        char c = (char)(p.se+'a');
        out<<c<<" ";
        v.pop_back();
    }
    cout<<endl;

    return 0;
    ///return main();
}

///sin and cos expect input in radians not degrees. so use , sin(degrees * pi / 180)
