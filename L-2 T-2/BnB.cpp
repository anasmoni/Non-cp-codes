#include<bits/stdc++.h>
using namespace std;

typedef long long int lli;
typedef pair<int,int> pii;
typedef vector<int> vec;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define scn(n) scanf("%d",&n)
#define scnll(n) scanf("%lld",&n)
#define scn2(n,m) scanf("%d%d",&n,&m)
#define scn3(n,m,w) scanf("%d%d%d",&n,&m,&w)
#define scn2ll(n,m) scanf("%lld%lld",&n,&m)
#define atoz(v) v.begin(),v.end()
#define Fill(a,v) memset(a,v,sizeof(a))
#define sz(v) v.size()
#define fi first
#define se second
#define inf 1e9
#define pi acos(-1.0)
#define sqr(x) x*x
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define N 100005

vector<int>SS[N]; /// input sub sets
vector<int>res_SS; /// result sub set
int n,m, ans=inf;

/**
Lower bound = Number of sets picked so far + (Number of elements not covered so far)/(Maximum cardinality of the
remaining sets)
**/

struct Node
{
    int lb;
    set<int>ar;     /// elements taken to reach this node
    vector<int>which;  /// resulting sub sets;

    Node( int l)
    {
        lb = l; /// set lower bound;.....as it's a minimization problem
    }
};

void BnB(Node root, int ith)
{

    if(root.lb>=ans)return; ///  pruning....sub tree with this root has Lower_bound >= ans...so ignore this sub tree..
    /// ...cause best result we can get from this sub tree = root.lb

    if(root.ar.size()==n)/// found universe set
    {
        if(ans>root.lb)
        {
            ans = root.lb;
            res_SS.clear(); /// clear prev result set as we found better one

            res_SS = root.which;
        }
        return; /// we need not to go deeper.....
    }

    if(ith>m)return; /// no more input sub sets left;

    //cout<<ith<<" "<<root.lb<<" "<<root.ar.size()<<endl;

    Node right(1);
    right.ar=root.ar;
    right.which = root.which;
    right.which.pb(ith);

    for(auto x : SS[ith])
    {
        right.ar.insert(x);
    }

    right.lb = root.lb + (right.ar.size()<n) ;

    Node left(root.lb); /// ignoring ith sub set
    left.ar = root.ar;
    left.which = root.which;

    BnB(right,ith+1);

    BnB(left,ith+1);
}

void Print()
{
    cout<<ans<<endl;

    for(auto i :res_SS)
    {
        for(auto x : SS[i])cout<<x<<" ";
        cout<<endl;
    }
}

void solve()
{

    Node root(1);

    BnB(root, 1);

    if(ans==inf)cout<<"Impossible";
    else Print();
}


int main()
{
    scn2(n,m);

    for(int x,i=1; i<=m; i++)
    {
        while(1)
        {
            char c;
            scanf("%d%c",&x,&c);
            SS[i].pb(x);
            if(c=='\n')break;
        }
    }

    solve();

    return 0;
}

/**

5 4
1 2 3
2 4
3 4
4 5

5 4
1 2 3 4 5
2 4
3 4
4 5


5 4
2 4
1
4 5
2 3 4 5

5 4
2 4
2
4 5
2 3 4 5

5 4
2 4
1 2 3 4 5
4 5
2 3 4


5 6
1
2
4
4 5
5
3

5 6
1 2 3
2
4
4 5
5
3

5 3
1 2 3
4
5

5 4
3 4 5
4
1 2 3 4
3 4

**/
