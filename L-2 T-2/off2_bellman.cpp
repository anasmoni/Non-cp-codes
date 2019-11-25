#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0


class HeapItem
{
public:
    int u,v,cost;
    HeapItem() {}
    HeapItem(int uu,int vv, int c)
    {
        u=uu;
        v=vv;
        cost=c;
    }
};

//****************Dynamic ArrayList class based************************
class ArrayList
{
    HeapItem * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(HeapItem hp) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    HeapItem getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new HeapItem[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(HeapItem hp)
{
    HeapItem * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new HeapItem[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = hp ; //store new item
    length++ ;
}




HeapItem ArrayList::getItem(int position)
{
    if(position < 0 || position >= length)
    {
        HeapItem h;
        return h;
    }
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  *adjList ;
    int *color;
    int *dist;
    int *parent;
    int *fin_time;
    int *disc_time;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int c);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph(bool dfs=false);
    void bfs(int source); //will run bfs in the graph
    void dfs(); //will run dfs in the graph
    void dfs_visit(int u,int &time);
    void Bellman(int n,int e,int s);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;
    dist=0;
    color=0;
    parent=0;
    fin_time = 0;
    disc_time = 0;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    color = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];
    fin_time = new int[nVertices];
    disc_time = new int[nVertices];
}

void Graph::addEdge( int u, int v, int c)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[0].insertItem(HeapItem(u,v,c)) ;
}

void Graph::Bellman(int n,int e,int s)
{

    for(int i=0; i<n; i++)
    {
        dist[i]=INFINITY;
        parent[i]=-1;
    }

    dist[--s]=0;

    for(int i=1; i<n; i++)
    {

        for(int j=0; j<e; j++)
        {
            HeapItem  h = adjList[0].getItem(j);
            int u = h.u;
            int v = h.v;
            int w = h.cost;
            //printf("%d %d %d\n",u,v,w);
            if(dist[u]!=INFINITY && dist[v] > dist[u] + w )
            {
                //printf("Ddffdf\n");
                dist[v] = dist[u]+w;
                parent[v]=u;
            }
        }
    }

    for(int j=0; j<e; j++)
    {

        HeapItem  h = adjList[0].getItem(j);
        int u = h.u;
        int v = h.v;
        int w = h.cost;

        if(dist[u]!=INFINITY && dist[v] > dist[u] + w)
        {
            printf("Negative Cycle?  Yes!\n");
            e=-1;
        }
    }

    if(e!=-1)
    {
        printf("The Source? %d\n",s);
        printf("V\tVd\tVp\n");

        for(int i=0; i<n; i++)
        {
            printf("%d\t",i+1);
            if(dist[i]!=INFINITY)printf("%d\t",dist[i]);
            else printf("INF\t");
            if(parent[i]!=-1)printf("%d\n",parent[i]);
            else printf("nill\n");

        }
        printf("Negative Cycle? No\n");
    }

}

Graph::~Graph()
{
    if(adjList)delete[]adjList;
    if(dist)delete[]dist;
    if(color)delete[]color;
    if(parent)delete[]parent;
    if(fin_time)delete[]fin_time;
    if(disc_time)delete[]disc_time;

    adjList = 0 ;
    dist=0;
    color=0;
    parent=0;
    fin_time = 0;
    disc_time = 0;
}

int main()
{
    int n,d=1,t,e;



    scanf("%d%d", &n,&e);
    Graph g(d==1);
    g.setnVertices(n);
    bool df=false;

    for(int i=0; i<e; i++)
    {

        int c,u,v;
        scanf("%d%d%d", &u, &v,&c);
        g.addEdge(--u,--v,c);
    }

    while(true)
    {
        int s;
        printf("Enter Source...or 0 to exit...\n");
        scanf("%d",&s);
        if(!s)break;
        g.Bellman(n,e,s);
    }

    return 0;

}

/**
5 8
1 3 6
1 4 3
2 1 3
3 4 2
4 2 1
4 3 1
5 2 4
5 4 2

7 10
7 1 2
6 1 -7
1 3 7
1 2 -1
3 6 -7
3 4 -4
4 3 -2
4 2 3
2 5 2
5 4 -7


7 9
7 1 2
6 1 -7
1 3 7
1 2 -1
3 6 -7
4 3 -2
4 2 3
2 5 2
5 4 -7

**/
