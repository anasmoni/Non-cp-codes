#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0
#define GREY 1
#define BLACK 2

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


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int *dist;
	int *color;
    int *parent;
    int *fin_time;
    int *disc_time;

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
    void printGraph(bool dir=false);
	void bfs(int source); //will run bfs in the graph
	void dfs();
	void dfs_visit(int u , int &time);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	dist=0;
	color=0;
	parent=0;
	fin_time = 0;
    disc_time = 0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
	color = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];
    fin_time = new int[nVertices];
    disc_time = new int[nVertices];


    matrix = new int*[nVertices];

    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices){printf("Edge doesn't axist\n"); return;}

    matrix[u][v]=0;

    if(!directed) matrix[v][u] = 0;

    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        printf("vertex out of range\n");
        return false;
    }
    return matrix[u][v]==1;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices){printf("Vertex doesn't axist\n"); return -1;}

    int cnt=0;
    for(int i=0 ; i<nVertices; i++)cnt += (matrix[u][i]==1);
    return cnt;
    //returns the degree of vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        printf("vertex out of range\n");
        return false;
    }

    for(int i=0 ; i<nVertices ; i++){
        if(matrix[u][i]==1 && matrix[v][i]==1 && i!=u && i!=v)return true;
    }
    return false;
    //returns true if vertices u and v have common adjacent vertices

}

void Graph::bfs(int source)
{
    if(matrix==0)return;
    if(source<0 || source>=nVertices){printf("Vertex out of bound......\n"); return;}
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
        int u = q.dequeue();
        for(int i=0 ; i<nVertices ; i++){

            if(isEdge(u,i)==false)continue;

            if(color[i]==WHITE){
                dist[i] = dist[u]+1;
                color[i] = GREY;
                parent[i] = u;
                q.enqueue(i);
            }
        }
        color[u] = BLACK;
        //complete this part
    }

}

void Graph::dfs_visit(int u , int &time){

    disc_time[u] = ++time;
    color[u] = GREY;
    for(int i=0 ; i<nVertices ; i++){
        if(isEdge(u,i) && color[i]==WHITE){
            parent[i]=u;
            dfs_visit(i,time);
        }
    }
    color[u]=BLACK;
    fin_time[u]=++time;
}

void Graph::dfs()
{
    if(matrix==0)return;

    for(int i=0 ; i<nVertices ; i++){
        color[i] = WHITE ;
        parent[i] = -1 ;
        fin_time[i]=0;
        disc_time[i]=0;
    }
    int time=0;

    for(int i=0  ; i<nVertices ; i++){
        if(color[i]==WHITE){
            dfs_visit(i,time);
        }
    }


    //write this function
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices){printf("Vertex out of bound......\n"); return INFINITY;}

    bfs(u);
    return dist[v];
}


void Graph::printGraph(bool dir)
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);

        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        if(dir)printf(" dfs -> %d %d",disc_time[i],fin_time[i]);
        printf("\n");
    }
}

Graph::~Graph()
{
    if(matrix)delete[]matrix;
    if(dist)delete[]dist;
    if(color)delete[]color;
    if(parent)delete[]parent;
    if(fin_time)delete[]fin_time;
    if(disc_time)delete[]disc_time;

    matrix = 0 ;
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
            g.printGraph();
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
            g.printGraph(d==1);
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
