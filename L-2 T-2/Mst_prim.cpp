#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int u,cost;
    Node() {}
    Node(int uu, int c)
    {
        u=uu;
        cost=c;
    }
};

bool operator<(Node A,Node B)
{
    if(A.cost>B.cost){
        return true;
    }
    else if (A.cost==B.cost){
        return A.u>B.u;
    }
    else return false;//printing the min vertex...while cost is equal
}

class HeapItem
{
public:
    int u; //actual data that is stored
    int cost; //key value of the data, heap is constructed based on key
    HeapItem() {}
    HeapItem(int uu,int c)
    {
        u=uu;
        cost=c;
    }
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;
    int * map;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
        A[0].cost = MAXREAL;
    }

    ~MinHeap() //destructor
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0; //set to NULL after deletion
        A = 0; //set to NULL after deletion
    }


    void insertItem(int uu, int c)
    {

        /* if((map[uu]<=heapLength )&& map[uu]>0)
         {

             updateKey(uu,c);
             return;
         }*/
        HeapItem t;
        t.u=uu;
        t.cost=c;

        A[++heapLength] = t;
        map[t.u] = heapLength;

        buHeapify(heapLength);

    }

    bool Empty()
    {
        return heapLength==0;
    }

    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {


        HeapItem ret = A[1];
        A[1] = A[heapLength--];
        heapify(1);

        return ret;

    }


    //The function updates the key value of an existing data
    //stored in the heap
    //Note that updates can result in an increase or decrease of key value
    //Call to heapify or buheapify is required
    void updateKey(int u, int c)
    {
        //printf("asa-> %d\n",map[data]);
        if(map[u]>heapLength || map[u]<=0)
        {
            printf("Element doesn't exist......\n");
            return;
        }
        A[map[u]].cost = c;

        buHeapify(map[u]);

    }


    //This function returns the key value of a data stored in heap
    int getKey(int u)
    {
        int i = map[u];
        return A[i].cost;
    }

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property

    void swap_node(int i,int j)
    {
        HeapItem t;
        t=A[i];
        A[i]=A[j];
        map[A[i].u]=i;
        A[j]=t;
        map[A[j].u]=j;

    }

    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;

            if(l>heapLength && r>heapLength) break; //nothing to do, we are at bottom

            else if(r>heapLength) smallest = l;

            else if(l>heapLength) smallest = r;

            else if( A[l].cost < A[r].cost )smallest = l;
            else if( A[l].cost > A[r].cost )smallest = r;
            else
            {
                if(A[l].u < A[r].u )smallest=l;
                else smallest=r;
            }


            if(A[i].cost < A[smallest].cost || (A[i].cost == A[smallest].cost && A[i].u < A[smallest].u)  ) break;
            else
            {
                swap_node(i,smallest);
                i = smallest;
            }

        }
    }

    void buHeapify(int i)
    {
//(A[i].cost == A[i/2].cost && A[i].u < A[i/2].u)
        while( i>1 && ( (A[i].cost < A[i/2].cost) || ((A[i].cost == A[i/2].cost) && (A[i].u < A[i/2].u)  )  )  )
        {
            swap_node(i,i/2);
            i = i/2;
        }
    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%d) ", A[i].u, A[i].cost);
        }
        printf("\n");
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
    ArrayList  * adjList ;
    int *color;
    int *dist;
    int *parent;
    int *fin_time;
    int *disc_time;
    int *takenby;
    int *cost;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation


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
    void prim();
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
    cost=0;
    takenby=0;
    //set direction of the graph
    //define other variables to be initialized

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
    cost = new int[nVertices];
    takenby = new int[nVertices];
}

void Graph::addEdge(int u, int v, int c)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(HeapItem(v,c)) ;
    adjList[v].insertItem(HeapItem(u,c)) ;
}


void Graph::prim()
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        takenby[i] = -1 ;
        cost[i] = INFINITY ;
    }


    MinHeap heap;
    heap.insertItem(0,0);
    cost[0]=0;
    int ans=0;
    priority_queue<Node>pq;
    pq.push(Node(0,0));

    while(!pq.empty() )//!heap.Empty() )
    {
       // heap.printHeap();
        //HeapItem hi = heap.removeMin();
        Node x = pq.top();
        pq.pop();
        int len = adjList[x.u].getLength();


        if(color[x.u]!=WHITE)continue;
        color[x.u]=GREY;
        //ans += hi.cost;
         ans += x.cost;

        for(int i=0 ; i<len ; i++)
        {
            HeapItem h = adjList[x.u].getItem(i);

            //printf("ddfd %d\n",h.cost);

            if(color[h.u]==GREY)continue;

            if(h.cost < cost[h.u])
            {
                //heap.insertItem(h.u,h.cost);
                cost[h.u]=h.cost;
                takenby[h.u]=x.u;
                pq.push(Node(h.u,h.cost));
            }
            else if(takenby[h.u]>x.u && h.cost == cost[h.u]) takenby[h.u] = x.u;
        }
    }

     for(int i=0; i<nVertices; i++)
    {
        if(takenby[i]!=-1){
            printf("%d %d\n",takenby[i],i);
        }
    }

    printf("%d\nfinito\n\n",ans);
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
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************


int main()
{
    freopen("input.txt", "r", stdin);
    int n,d=0,t,e;
    scanf("%d", &t);

    while(t--)
    {
        scanf("%d%d", &n,&e);
        Graph g(d==1);
        g.setnVertices(n);
        bool df=false;

        while(e--)
        {

            int c,u,v;
            scanf("%d%d%d", &u, &v,&c);
            g.addEdge(u, v,c);
        }

        g.prim();
    }
}





/**
dfs/dir
1 0 1
1 0 4
1 1 2
1 1 4
1 2 5
1 5 1
1 6 7
1 6 3
1 7 3
1 7 6
1 3 0
1 3 4
1 4 5

bfs
1 0 1
1 0 4
1 1 2
1 1 4
1 1 5
1 2 5
1 2 6
1 3 7
1 4 5
1 1 6
1 7 6

7

6 9
2 4 4
1 3 1
1 4 3
2 3 4
3 4 2
3 6 4
4 6 6
5 6 2
1 2 4

3 3
1 3 2
1 2 1
2 3 1

6 6
1 2 2
2 3 2
3 6 2
5 6 2
4 5 2
1 4 2

6 7
1 2 2
2 3 2
5 2 1
3 6 2
5 6 2
4 5 2
1 4 2

6 8
1 6 1
1 2 2
2 3 2
5 2 1
3 6 2
5 6 2
4 5 2
1 4 2

6 9
1 6 1
1 2 2
5 3 1
2 3 2
5 2 1
3 6 2
5 6 2
4 5 2
1 4 2

8 13
1 6 1
1 2 2
5 3 1
2 3 2
5 2 1
3 6 2
5 6 2
4 5 2
1 4 2
7 8 2
4 7 2
1 7 2
4 8 2

*/

/**
1 2
1 3
3 4
6 5
3 6
13
finito

1 2
2 3
2
finito

1 2
2 3
1 4
4 5
3 6
10
finito

1 2
2 3
1 4
2 5
3 6
9
finito

1 2
2 3
1 4
2 5
1 6
8
finito

1 2
5 3
1 4
2 5
1 6
7
finito

5 2
5 3
1 4
1 2
1 6
1 7
4 8
11
finito
*/
