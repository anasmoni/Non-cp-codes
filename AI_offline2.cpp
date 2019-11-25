#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long int lli;
typedef unsigned long long int ulli;
typedef pair<int,int> pii;

#define ones(x) __builtin_popcount(x)
#define onesl(x) __builtin_popcountl(x)
#define onesll(x) __builtin_popcountll(x)

#define pb push_back
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

#define Bsize 101

#define HAMMING 1
#define MANHATTAN 2
#define LINEAR 3

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

int n, ON_PLAY;
vector<int>Goal_Board[Bsize];

string who[5] = {"none","Hamming","Manhattan","Linear"};

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int Right_Tile(int i, int j)
{
    if(i==j && i==n) return 0;
    return ((i-1)*n + j);
}

int Right_row(int num)
{

    return ( (num/n) + (num%n != 0) );
}

int Right_col(int num)
{

    return ( num%n ? num%n : n );
}

int Count_Inversion(vector<int> *Board)
{

    ordered_set os;
    int inv = 0;

    for(int i=n; i ; i--)
    {
        for(int j=n; j ; j--)
        {
            if(Board[i][j])
            {
                inv += os.order_of_key(Board[i][j]);

                os.insert(Board[i][j]);
            }
        }
    }
    return inv;
}

bool isImpossible(int Blank_Row, vector<int> *Board)
{

    int inv = Count_Inversion(Board);

    if(n%2 && inv%2) return true;

    else if(n%2 == 0 && (inv+Blank_Row-1)%2 == 0) return true;

    return false;
}

int Hamming_dist(vector<int> *Board)
{

    int wrong_pos = 0;

    for(int i=1; i<=n; i++)
    {

        for(int j=1; j<=n; j++)
        {

            if(Board[i][j] && Right_Tile(i,j) != Board[i][j]) wrong_pos++;
        }
    }

    return wrong_pos;
}

int Manhattan_dist(vector<int> *Board)
{

    int sum = 0;

    for(int i=1; i<=n; i++)
    {

        for(int j=1; j<=n; j++)
        {

            if(Board[i][j] == 0) continue;

            sum += (abs(i-Right_row(Board[i][j]) ) + abs(j-Right_col(Board[i][j]) ) );
        }
    }
    return sum;
}

int Linear_Conflict(vector<int> *Board)
{

    int man = Manhattan_dist(Board), conf = 0;

    for(int i=1; i<=n; i++)
    {

        int horizontal_mx = -1;

        for(int j=1; j<=n; j++)
        {

            if(Board[i][j] == 0) continue;

            int rr = Right_row( Board[i][j] );

            if(rr == i)
            {

                if(Board[i][j] > horizontal_mx)
                {
                    horizontal_mx = Board[i][j];
                }
                else conf++;
            }
        }
    }

    for(int j=1; j<=n; j++)
    {

        int vertical_mx = -1;

        for(int i=1; i<=n; i++)
        {

            if(Board[i][j] == 0) continue;

            int rc = Right_col( Board[i][j] );

            if(rc == j)
            {

                if(Board[i][j] > vertical_mx)
                {
                    vertical_mx = Board[i][j];
                }
                else conf++;
            }
        }
    }

    return (man + 2*conf);
}

struct Node
{

    vector<int>Board[Bsize];
    vector<Node>Prev;
    int moves ;
    pii Blank_rc;

    Node(vector<int> *B, int m, pii bp)
    {

        moves = m;

        for(int i=1; i<=n; i++) Board[i] = B[i];

        Blank_rc = bp;
    }
};

int Calc_Cost(Node A)
{

    int CostA = A.moves;

    if(ON_PLAY == HAMMING)
    {

        CostA += Hamming_dist(A.Board);
    }
    else if(ON_PLAY == MANHATTAN)
    {

        CostA += Manhattan_dist(A.Board);
    }
    else
    {
        CostA += Linear_Conflict(A.Board);
    }

    return CostA;
}

bool operator<(Node A, Node B)
{
    return (Calc_Cost(A)<=Calc_Cost(B));
}

bool operator==(Node A, Node B)
{

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(A.Board[i][j] != B.Board[i][j]) return false;
        }
    }
    return true;
}

bool indexOK(int i, int j)
{

    return (i>=1 && j>=1 && i<=n && j<=n);
}

bool isVisited(vector<Node> &Closed_List, Node now)
{

    for(int i=0; i<Closed_List.size(); i++)
    {
        if(Closed_List[i] == now) return true;
    }
    return false;
}

void Print_Board(Node node)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++) cout<<node.Board[i][j]<<" ";
        cout<<endl;
    }
}
/*
7 2 4
6 0 5
8 1 3
*/
void Solve(vector<int> *Board, pii Blank_rc)
{

    multiset<Node>Open_List;

    vector<Node>Closed_List;

    Node curr(Board,0,Blank_rc);
    curr.Prev.pb(curr);
    Node Goal(Goal_Board,0,pii(n,n));

    Open_List.insert(curr);

    while( Open_List.size())
    {

        auto it = Open_List.begin();
        curr = *it;
        Open_List.erase(it);

        Closed_List.pb(curr);

       // Print_Board(curr);
        //cout<<curr.moves<<endl;;

        if(Goal == curr)
        {
            cout<<"\n"<<who[ON_PLAY]<<" : \n";
            cout<<"      Moves : "<<curr.moves<<endl;
            cout<<"      Node Expanded : "<<Closed_List.size()<<endl;
            cout<<"      Node Visited : "<<(Closed_List.size() + Open_List.size())<<"\n\n";

            vector<Node>path;

            while(1)
            {
                path.pb(curr);
                if(curr == curr.Prev[0])break;
                curr = curr.Prev[0];
            }

            for(int i=path.size()-1 ,m=0; i>=0 ; i--,m++)
            {
                cout<<"Move "<<m<<"\n----------\n";
                Print_Board(path[i]);
                cout<<"\n\n";
            }

            return;
        }

        for(int i=0; i<4; i++)
        {

            int ii = curr.Blank_rc.fi + dx[i];
            int jj = curr.Blank_rc.se + dy[i];

            if(indexOK(ii,jj) == false) continue;

            Node now(curr.Board,curr.moves+1, pii(ii,jj));
            now.Prev.pb(curr);

            swap(now.Board[ii][jj], now.Board[ curr.Blank_rc.fi ][ curr.Blank_rc.se ] );

            if(isVisited(Closed_List, now)) continue;

            Open_List.insert(now);

            /*cout<<"parent\n";
            Print_Board(curr);
            cout<<"\n__________\n";
            Print_Board(now);
            cout<<"\n________\n";*/
        }

    }

}

int main()
{

    cout<<"Enter Board Size...\n";

    cin>>n;

    cout<<"Enter the board...\n";

    vector<int>Board[Bsize];

    pii Blank_rc;

    for(int i=1; i<=n; i++)
    {

        Board[i].pb(-1);
        Goal_Board[i].pb(-1);

        for(int j=1,B; j<=n; j++)
        {

            cin>>B;

            Board[i].pb(B);
            Goal_Board[i].pb(Right_Tile(i,j));

            if(B==0)
            {
                Blank_rc = pii(i,j);
            }
        }
    }

    if(isImpossible(Blank_rc.fi,Board))
    {
        cout<<"Impossible";
        return 0;
    }

    for(int i=1; i<=3; i++)
    {
        ON_PLAY = i;
        Solve(Board,Blank_rc);
    }

    return 0;
}
