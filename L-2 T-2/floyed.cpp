#include <bits/stdc++.h>
using namespace std;
#define INF 900000
#define ninf -INF

int d[100][100], pm[100][100],pre[100][100];

void init(int n)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(i==j)d[i][j]=0;
            else d[i][j]=INF;

            pm[i][j]=pre[i][j] =INF;
        }
    }
}

void print(int n, int yup=0)
{

    if(yup)
    {

        for(int k=1; k<=n; k++)
        {
            for(int i=1 ; i<=n; i++)
            {

                if(pre[k][i]==INF)printf("INF\t");
                else printf("%d\t",pre[k][i]);
            }
            cout<<endl;
        }
        cout<<endl;

        return ;
    }

    for(int k=1; k<=n; k++)
    {
        for(int i=1 ; i<=n; i++)
        {

            if(d[k][i]==INF)printf("INF\t");
            else printf("%d\t",d[k][i]);
        }
        cout<<endl;
    }
    cout<<endl;
}


void floyed(int n)
{
    cout<<"Initial graph:\n\n";
    print(n);


    for(int k=1; k<=n; k++)
    {
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(i==k || k==j || d[i][k]==INF || d[k][j]==INF)continue;

                int dist=d[i][k]+d[k][j];

                if(dist<d[i][j]){

                    d[i][j]=dist;
                    pre[i][j]=pre[k][j];
                }

            }
        }
    }

    cout<<"All pair shortest paths:\n\n";
    print(n);


    cout<<"Predecessor Matrix:\n\n";

    print(n,1);



}


int main()
{


    int n,m;
    scanf("%d %d",&n,&m);

    init(n);

    for(int i=0; i<m; i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        d[u][v]=w;
        pre[u][v]=u;

    }

    floyed(n);

    return 0;
}

/***

5
8
1 3 6
1 4 3
2 1 3
3 4 2
4 2 1
4 3 1
5 2 4
5 4 2


7
12
2 6 -6
6 7 4
7 1 1
6 1 8
1 3 6
1 4 3
2 1 3
3 4 2
4 2 1
4 3 1
5 2 4
5 4 2
***/


/***
#include <bits/stdc++.h>
using namespace std;
#define INF 900000
#define ninf -INF

int d[100][100], pm[100][100], edg[100][100] ;

void init(int n)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(i==j)d[i][j]=0;
            else d[i][j]=INF;

            pm[i][j] =INF;
            edg[i][j]=ninf;
        }
    }
}

void print(int n, int yup=0)
{

    if(yup)
    {

        for(int k=1; k<=n; k++)
        {
            for(int i=1 ; i<=n; i++)
            {

                if(pm[k][i]==INF)printf("INF\t");
                else printf("%d\t",pm[k][i]);
            }
            cout<<endl;
        }
        cout<<endl;

        return ;
    }

    for(int k=1; k<=n; k++)
    {
        for(int i=1 ; i<=n; i++)
        {

            if(d[k][i]==INF)printf("INF\t");
            else printf("%d\t",d[k][i]);
        }
        cout<<endl;
    }
    cout<<endl;
}


void floyed(int n)
{
    cout<<"Initial graph:\n\n";
    print(n);


    for(int k=1; k<=n; k++)
    {
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(i==k || k==j || d[i][k]==INF || d[k][j]==INF)continue;

                int dist=d[i][k]+d[k][j];

                if(dist<d[i][j]){

                    d[i][j]=dist;

                    if(edg[i][j]!=ninf  && d[i][j]!=edg[i][j])

                        edg[i][j] = ninf;
                }

            }
        }
    }

    cout<<"All pair shortest paths:\n\n";
    print(n);


   for(int k=1; k<=n; k++)
    {
        for(int i=1; i<=n; i++)
        {

            for(int j=1; j<=n; j++)
            {
                if(edg[j][i]!=ninf  && d[j][i] + d[k][j] == d[k][i]){
                    pm[k][i]=j;
                    break;
                }
            }
        }
    }



    cout<<"Predecessor Matrix:\n\n";

    print(n,1);



}


int main()
{


    int n,m;
    scanf("%d %d",&n,&m);

    init(n);

    for(int i=0; i<m; i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        d[u][v]=w;
        edg[u][v]=w;
    }

    floyed(n);

    return 0;
}

****/
