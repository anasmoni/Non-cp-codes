#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
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
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation


public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph(bool dfs=false);
    void bfs(int source); //will run bfs in the graph
    void dfs(); //will run dfs in the graph
    void dfs_visit(int u,int &time);
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
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        printf("vertex out of range\n");
        return;
    }

    adjList[u].removeItem(v);
    if(!directed)adjList[v].removeItem(u);

}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        printf("vertex out of range\n");
        return false;
    }

    return adjList[u].searchItem(v)!=NULL_VALUE;// || adjList[v].searchItem(u)!=NULL_VALUE;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices)
    {
        printf("vertex out of range\n");
        return -1;
    }

    return adjList[u].getLength();
    //returns the degree of vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        printf("vertex out of range\n");
        return false;
    }

    int len = adjList[u].getLength();

    for(int i=0 ; i<len; i++)
    {
        int temp = adjList[u].getItem(i);
        if(adjList[v].searchItem(temp)!=NULL_VALUE)return true;
    }
    return false;
    //returns true if vertices u and v have common adjacent vertices

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }

    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;

    while( !q.empty() )
    {
        int t = q.dequeue();
        int len = adjList[t].getLength();

        for(int i=0 ; i<len ; i++)
        {

            int v = adjList[t].getItem(i);

            if(color[v]==WHITE)
            {
                color[v]=GREY;
                dist[v] = dist[t]+1;
                parent[v]=t;
                q.enqueue(v);
            }
        }
        color[t] = BLACK;
        //complete this part
    }
}

void Graph::dfs_visit(int u , int &time)
{
    if(u<0 || u>=nVertices)
    {
        printf("vertex out of range\n");
        return;
    }

    disc_time[u] = ++time;
    color[u] = GREY;
    int len = adjList[u].getLength();

    for(int i=0 ; i<len ; i++)
    {

        int v = adjList[u].getItem(i);

        if(color[v]==WHITE)
        {
            parent[v]=u;
            dfs_visit(v,time);
        }
    }

    color[u]=BLACK;
    fin_time[u]=++time;
}

void Graph::dfs()
{
    if(adjList==0)return;

    for(int i=0 ; i<nVertices ; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        fin_time[i]=0;
        disc_time[i]=0;
    }

    int time=0;

    for(int i=0  ; i<nVertices ; i++)
    {
        if(color[i]==WHITE)
        {
            dfs_visit(i,time);
        }
    }

}

int Graph::getDist(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        printf("vertex out of range\n");
        return INFINITY;
    }

    bfs(u);
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return dist[v];
}

void Graph::printGraph(bool dfs)
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }

        if(dfs)printf(" dfs -> %d %d",disc_time[i],fin_time[i]);
        printf("\n");
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
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************


int main(void)
{
    int n,d=0;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter 1 if directed else 0: ");
    scanf("%d", &d);
    Graph g(d==1);
    g.setnVertices(n);
    bool df=false;

    while(1)
    {
        printf("1. Add edge. 2.hasCommonAdjacent 3.getDist.\n");
        printf("4.bfs . 5. Print Graph  6. Exit.\n");
        printf("7.dfs. 8. getDegree. 9.removeEdge. \n\n");

        int ch,u,v;
        scanf("%d",&ch);
        if(ch==1)
        {
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u,v))printf("yes\n");
            else printf("no\n");
        }
        else if(ch==3)
        {
            scanf("%d%d", &u, &v);
             u = g.getDist(u,v);
            if(u==INFINITY)printf("not connected....\n");
            else printf("distance -> %d\n",u);
        }
        else if(ch==5)
        {
            g.printGraph(df);
            df = false;
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==4){
            scanf("%d",&u);
            g.bfs(u);
        }
        else if(ch==7){
            g.dfs();
            df = true;
        }
        else if(ch==8){
            scanf("%d",&u);
            printf("%d\n",g.getDegree(u));
        }
        else if(ch==9)
        {
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
        }
        printf("\n\n");
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
*/
