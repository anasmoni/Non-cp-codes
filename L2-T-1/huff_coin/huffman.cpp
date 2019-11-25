#include<bits/stdc++.h>
#define MAX 100

using namespace std;

struct Node
{
    char c;
    int f;
    struct Node *left, *right;
};

class MinHeap
{
public:

    int len;
    struct Node **A;

    MinHeap(int cp)
    {
        len = cp;
        A = (struct Node**)malloc(MAX * sizeof(struct Node*));
    }

};

class Myclass
{
public:

    Myclass() {}

    struct Node* newNode(char c, int f)
    {
        struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
        temp->c = c;
        temp->f = f;
        temp->left = 0;
        temp->right = 0;
        return temp;
    }

    void swap_Node(struct Node** a, struct Node** b)
    {
        struct Node* t = *a;
        *a = *b;
        *b = t;
    }

    void heapify(MinHeap *meap ,  int idx)
    {

        int smallest,lo,hi;


        smallest = idx;
        lo = 2 * idx + 1;
        hi = 2 * idx + 2;

        if (lo < meap->len && meap->A[lo]->f < meap->A[smallest]->f)smallest = lo;

        if (hi < meap->len && meap->A[hi]->f < meap->A[smallest]->f)smallest = hi;
        if(smallest!=idx)
        {
            swap_Node(&meap->A[smallest],&meap->A[idx]);
            //idx = smallest;
            //printf("debug");
            heapify(meap,smallest);
        }

        //printf("dfdf");

    }

    struct Node* Get_Min(MinHeap *meap)
    {
        struct Node* temp = meap->A[0];
        meap->A[0] = meap->A[meap->len - 1];
        --meap->len;
        heapify(meap, 0);
        // printf("bug");
        return temp;
    }

    void insertItem(MinHeap* meap, struct Node* Node)
    {
        ++meap->len;
        int i = meap->len - 1;

        while (i && Node->f < meap->A[(i - 1)/2]->f)
        {
            meap->A[i] = meap->A[(i - 1)/2];
            i = (i - 1)/2;
        }
        meap->A[i] = Node;
    }

    MinHeap* init(char C[], int fre[], int len)
    {
        MinHeap mp(len);
        MinHeap *meap = &mp;

        for (int i = 0; i < len; ++i)meap->A[i] = newNode(C[i], fre[i]);

        meap->len = len;
        int n=len-1;
        for (int i = (n - 1) / 2; i >= 0; --i) heapify(meap, i);
        return meap;
    }


    void print_code(struct Node* root,string s)
    {
        if (root->left)print_code(root->left,s+"0");

        if (root->right)print_code(root->right,s+"1");

        if (!(root->right) && !(root->left)){
            printf("%c: ", root->c);
            cout<<s<<" "<<s.size()-1<<endl;
        }
    }

    void Solve(char C[], int fre[], int len)
    {

        struct Node *left, *right, *root;

        MinHeap* meap = init(C, fre,len);

        while (meap->len!=1)
        {
            left = Get_Min(meap);
            right = Get_Min(meap);

            root = newNode('i', left->f + right->f);// i internal node.....

            root->left = left;
            root->right = right;
            //printf("bug");

            insertItem(meap, root);

        }
//        printf("bug");

        struct Node* node =  Get_Min(meap);

        print_code(node," ");
    }

};



int main()
{

    while(true)
    {
        printf("Enter 0 to exit.....\n");
        int n;
        scanf("%d",&n);

        if(!n)break;

        char C[n+1];
        int fre[n+1];
        int zero=0;
        int taken[26];
        memset(taken,0,sizeof(taken));

        for(int i=0 ; i<n ; i++){
            cin>>C[i-zero]>>fre[i-zero];
            zero+=(fre[i-zero]<=0 || taken[C[i-zero]-'a']);
            taken[C[i-zero]-'a']=1;
        }

        n-=zero;

        if(n==1)cout<<C[0]<<": "<<1<<endl;
        else if(n)
        {
            Myclass mc;
            mc.Solve(C,fre,n);
        }
    }
    return 0;
}



