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
#define inf INT_MAX
#define pi acos(-1.0)
#define sqr(x) x*x
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define L 500

vector<int>G[L];
int  flow[L][L], flowed[L][L], cut[L][L];
int n,m,s,t;
int pre[L],cost[L];
///use adj matrix always
bool bfs()
{

    queue<int> q;
    int u;

    Fill(pre,-1);
    cost[s] = inf;
    pre[s] = s;
    q.push(s);

    while(!q.empty())
    {
        u = q.front();
        q.pop();
        if(u==t)return true;

        for(auto i : G[u])
        {
            if(pre[i]==-1&&flow[u][i]>0)
            {
                cost[i] = min(cost[u],flow[u][i]);
                pre[i] = u;
                q.push(i);
            }
        }
    }
    return false;
}

int ford()
{
    int maxflow=0;

    while(bfs())
    {
        maxflow +=cost[t];
        int u = t;

        while(u!=pre[u])
        {
            flow[pre[u]][u] -=cost[t];

            flowed[pre[u]][u] +=cost[t];

            flow[u][pre[u]] +=cost[t];

            u = pre[u];

        }
    }

    return maxflow;

}

bool iscut(int u, int v)
{
    return (flowed[u][v]==flow[v][u] && !flow[u][v]);
}


void print(bool mc=false)
{

    queue<int> q;
    int u;

    Fill(pre,0);
    pre[s] = s;
    q.push(s);

    while(!q.empty())
    {
        u = q.front();
        q.pop();

        for(auto i : G[u])
        {
            if(!mc)
            {
                cout<<"Edge "<<u<<" -> "<<i<<"\tFlow: "<<flowed[u][i]<<endl;

                if( !pre[i])
                {
                    pre[i] = 1;
                    q.push(i);
                }
            }
            else{
                if(iscut(u,i))cout<<"Edge "<<u<<" -> "<<i<<endl;
                else if( !pre[i])
                {
                    pre[i] = 1;
                    q.push(i);
                }
            }
        }
    }
}

int main()
{

    Fill(flow,0);
    Fill(flowed,0);
    Fill(cut,0);

    scn3(m,s,t);

    for(int j=1,u,v,c ; j<=m; j++)
    {
        scn3(u,v,c);

        flow[u][v] += c;
        G[u].pb(v);
    }

    cout<<"\nMax Flow : "<<ford()<<endl<<endl;

    print();

    cout<<"\nMin Cut Edges\n";

    print(true);




    return 0;
}

/**

10 1 5

1 2 16
1 6 13
2 6 10
2 3 12
3 6 9
3 5 20
6 2 4
6 4 14
4 5 4
4 3 7


6 1 4
1 2 12
2 3 12
3 4 12
1 5 4
5 6 4
6 4 4

8 1 5

1 2 12
2 4 10
4 5 20
1 3 20
3 2 30
3 4 15
3 6 5
6 5 5

**/
