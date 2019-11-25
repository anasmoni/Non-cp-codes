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

#define Heuristic1 1
#define Heuristic2 2
#define Heuristic3 3
#define Heuristic4 4
#define MAX_depth 3

int player1_Heuristic , player2_Heuristic , w1,w2,w3,w4;

struct State{
    vector<int>player1 , player2;
    int storage1, storage2 , turn , captured1 , captured2 , extra_move1 , extra_move2;
};

State Init_Game(State state){

    for(int i=1; i<=6; i++){
        state.player1.pb(4);
        state.player2.pb(4);
    }
    state.storage1 = state.storage2 = 0;
    state.captured1 = state.captured2 = state.extra_move1 = state.extra_move2 = 0;
    state.turn = 1; /// 0 if opponent's turn

    return state;
}

bool Game_Over(State curr){

    int sum1 = 0 , sum2 = 0;

    for(int i=0; i<6; i++){
        sum1 += curr.player1[i];
        sum2 += curr.player2[i];
    }

    if(sum1 == 0 || sum2 == 0) return true;

    return false;
}

int Calc_Heuristic1(State curr){

    int ret = 0;

    ret = curr.storage1 - curr.storage2;

    return ret;
}

int Calc_Heuristic2(State curr){

    int side1,side2 ;
    side1 = side2 = 0;

    for(int i=0; i<6; i++){
        side1 += curr.player1[i];
        side2 += curr.player2[i];
    }

    int ret = Calc_Heuristic1(curr) * w1;

    ret += (side1 - side2)*w2;
    return ret;
}


int Calc_Heuristic3(State curr){

    int ret = Calc_Heuristic2(curr)  + w3 * curr.extra_move1;

    return ret;
}

int Calc_Heuristic4(State curr){

    int ret = Calc_Heuristic3(curr)  + w4 * curr.captured1;

    return ret;
}

int Utility(State curr){

    int ret = 0 , H = (curr.turn ? player1_Heuristic : player2_Heuristic);

    if(H == Heuristic1) ret = Calc_Heuristic1(curr);
    if(H == Heuristic2) ret = Calc_Heuristic2(curr);
    if(H == Heuristic3) ret = Calc_Heuristic3(curr);
    if(H == Heuristic4) ret = Calc_Heuristic4(curr);

    return ret;
}

int Mirror(int idx){

    for(int i=0 , j=5 ; i<6 ; i++,j--){
        if(idx == i) return j;
    }
}


State Move(State ret , int idx){

    if(ret.turn){
        int stones = ret.player1[idx];
        ret.player1[idx] = 0;

        for(int i=idx+1; i<6 && stones; i++){

            ret.player1[i]++;
            stones--;

            if(!stones && ret.player1[i]==0){
                ret.captured1 = 1 + ret.player2[Mirror(i)];
                ret.storage1 += 1 + ret.player2[Mirror(i)];
                ret.player2[Mirror(i)] = 0;
            }
        }

        if(stones){
            ret.storage1++;
            if(stones == 1) ret.extra_move1 = 1;
            stones--;
        }

        for(int i=0; i<6 && stones; i++){

            ret.player2[i]++;
            stones--;

            if(!stones && ret.player2[i]==0){
                ret.captured2 = 1 + ret.player1[Mirror(i)];
                ret.storage2 += 1 + ret.player1[Mirror(i)];
                ret.player1[Mirror(i)] = 0;
            }
        }

        if(stones) ret =  Move(ret,0);

        if(ret.extra_move1 == 0) ret.turn = 0;

    }
    else{

        int stones = ret.player2[idx];
        ret.player2[idx] = 0;

        for(int i=idx+1; i<6 && stones; i++){

            ret.player2[i]++;
            stones--;

            if(!stones && ret.player2[i]==0){
                ret.captured2 = 1 + ret.player1[Mirror(i)];
                ret.storage2 += 1 + ret.player1[Mirror(i)];
                ret.player1[Mirror(i)] = 0;
            }
        }

        if(stones){
            ret.storage2++;
            if(stones == 1) ret.extra_move2 = 1;
            stones--;
        }

        for(int i=0; i<6 && stones; i++){

            ret.player1[i]++;
            stones--;

            if(!stones && ret.player1[i]==0){
                ret.captured1 = 1 + ret.player2[Mirror(i)];
                ret.storage1 += 1 + ret.player2[Mirror(i)];
                ret.player2[Mirror(i)] = 0;
            }
        }

        if(stones) ret = Move(ret,0);

        if(ret.extra_move2 == 0) ret.turn = 1;

    }

    return ret;
}

int Max_Value(State curr , int alpha , int beta , int depth);
int Min_Value(State curr , int alpha , int beta , int depth);

int Max_Value(State curr , int alpha , int beta , int depth){

    if(depth == MAX_depth) return Utility(curr);

    int best = -inf;
    State Next;

    for(int i=0; i<6; i++){

        if(curr.player1[i] == 0) continue;

        Next = Move(curr,i);

        if(Next.turn) best = max(best , Max_Value(Next,alpha,beta,depth+1));
        else best = max(best , Min_Value(Next,alpha,beta,depth+1));

        if(best>=beta) return best;
        alpha = max(alpha , best);
    }
    return best;
}

int Min_Value(State curr , int alpha , int beta , int depth){

    if(depth == MAX_depth) return Utility(curr);

    int worst = inf;
    State Next;

    for(int i=0; i<6; i++){

        if(curr.player2[i] == 0) continue;

        Next = Move(curr,i);

        if(Next.turn) worst = min(worst , Max_Value(Next,alpha,beta,depth+1));
        else worst = max(worst , Min_Value(Next,alpha,beta,depth+1));

        if(worst<=alpha) return worst;
        beta = min(beta , worst);
    }
    return worst;
}

int Alpha_Beta_Search(State curr){

    int action = 0 , v = -inf;

    for(int i=0; i<6; i++){

        int k = Max_Value(curr,-inf,inf,0);
        if(k>v){
            v = k;
            action = i;
        }
    }
    return action;
}

pii Mancala(){

    State game;
    game = Init_Game(game);

    while(Game_Over(game)==false){

        int next_move = Alpha_Beta_Search(game);
        game = Move(game,next_move);
        ///for(int i=0; i<6; i++)cout<<game.player1[i]<<" "<<game.player2[i]<<endl;
        ///cout<<"\n+++++++++++++++++++++++++++++++++++++++++\n";
    }

    return pii(game.storage1>game.storage2 , game.storage1<game.storage2);
}

int main()
{
    ///freopen("output.txt","w",stdout);
    ///freopen("input.txt","r",stdin);

    ///FastIO;

    for(int i=1; i<=4; i++){
        for(int j=i+1; j<=4; j++){
            player1_Heuristic = i;
            player2_Heuristic = j;
            cout<<i<<" vs "<<j<<"   :  ";
            pii p = Mancala();
            cout<<p.fi<<" "<<p.se<<endl;
        }
    }

    return 0;
    ///return main();
}

///sin and cos expect input in radians not degrees. so use , sin(degrees * pi / 180)
