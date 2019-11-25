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
#define fill(a,v) memset(a,v,sizeof(a))
#define sz(v) v.size()
#define fi first
#define se second
#define inf 1e9
#define pi acos(-1.0)
#define sqr(x) x*x
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))

string up,don;
int m,mis,gap,row,col;
int M[101][101], G[101][101];

/**
 smith-waterman algo performs local sequence alignment;
that is, for determining similar regions between two strings of nucleic acid sequences or protein sequences.
 Instead of looking at the entire sequence
**/
void Local_Align(int i, int j, string u, string d)
{

    if(M[i][j]==0 )
    {
        reverse(atoz(u));
        reverse(atoz(d));
        //cout<<"SDFD";
        cout<<endl<<u<<"\n"<<d<<endl;
        return ;
    }

    if(up[j-1] == don[i-1])
    {
        u+=up[--j];
        d+=don[--i];
        //cout<<"DDF\n";
        Local_Align(i,j,u,d);
        //cout<<u<<" "<<d<<endl;
    }
    else if(M[i-1][j-1]+mis==M[i][j])
    {
        u+=up[--j];
        d+=don[--i];
        Local_Align(i,j,u,d);
    }
    else if(M[i-1][j]+gap==M[i][j])
    {
        u+="-";
        d+=don[--i];
        Local_Align(i,j,u,d);
    }
    else if(M[i][j-1]+gap==M[i][j])
    {
        d+="-";
        u+=up[--j];
        Local_Align(i,j,u,d);
    }

    // cout<<M[i][j]<<endl;

}

///Needleman–Wunsch algo for global alignment
void Global_Align(int i, int j, string u, string d)
{

    if(!i && !j)
    {
        reverse(atoz(u));
        reverse(atoz(d));
        //cout<<"SDFD";
        cout<<endl<<u<<"\n"<<d<<endl;
        return ;
    }

    if(up[j-1] == don[i-1])
    {


        u+=up[--j];
        d+=don[--i];
        Global_Align(i,j,u,d);
    }

    else if(G[i-1][j-1]+mis==G[i][j])
    {
        u+=up[--j];
        d+=don[--i];
        Global_Align(i,j,u,d);
    }

    else if(G[i][j-1]+gap==G[i][j])
    {
        d+="-";
        u+=up[--j];
        Global_Align(i,j,u,d);
    }

    else if(G[i-1][j]+gap==G[i][j])
    {
        u+="-";
        d+=don[--i];
        Global_Align(i,j,u,d);
    }
}

int main()
{
    int a;
    cin>>a>>a>>m>>mis>>gap;

    cin>>up>>don;

    col = up.size(), row = don.size();

    for(int i=0 ; i<=col; i++)
    {
        M[0][i]=0;
        G[0][i]=i*gap;
    }
    for(int i=0 ; i<=row; i++)
    {
        M[i][0]=0;
        G[i][0]=i*gap;
    }
    G[0][0]=0;

    int mx=-1;
    pii p;

    for(int i=1 ; i<=row; i++)
    {
        for(int j=1; j<=col; j++)
        {

            int s =  up[j-1]==don[i-1] ? m : mis;

            M[i][j] = max(0, max3( M[i-1][j-1]+s, M[i][j-1]+gap, M[i-1][j]+gap) ); /// for Local alignment

            G[i][j] = max3( G[i-1][j-1]+s, G[i][j-1]+gap, G[i-1][j]+gap);

            if(mx<M[i][j]){
                mx = M[i][j];
                p = pii(i,j);
            }
        }
    }



    cout<<endl<<"Local Alignment....\n\nScore: "<<mx<<endl;


    Local_Align(p.fi,p.se,"",""); /// begin from where the best local matched ended




    /**for(int i=0 ; i<=row; i++)
    {
        for(int j=0; j<=col; j++)cout<<M[i][j]<<"   ";
        cout<<endl;
    }**/

    cout<<"\n\nGlobal Alignment....\n\nScore : "<<G[row][col]<<endl;

    Global_Align(row,col,"",""); /// from the bottom right...as it is global alignment

    return 0;
}


/***
7 8 1 -1 -1
GCATGCT
GATTACAA

4 3 4 -1 -2
TGTTACGG
GGTTGACTA


AAACCC
CCCAAA
3 -2 -2

CGTGAATTCAT
GACTTAC
5 -3 -4

TACGGGCCCGCTAC
TAGCCCTATCGGTCA
4 -1 -1

4 4 1 -1 -1
TACGGGCCCGCTAC
TAGCCCTATCGGTCA


GCATGCU
GATTACA
1 -1 -1
***/

