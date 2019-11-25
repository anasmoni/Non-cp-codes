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
#define inf 1e9
#define pi acos(-1.0)
#define sqr(x) x*x
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define RED		1
#define BLACK	2

struct Tree
{
    int key;
    struct Tree *left, *right, *p;
    int color;
};

typedef struct Tree* Node;
struct Tree TNILL;
Node NIL = &TNILL;
Node tree;

void Print_Inorder(Node x)
{

    if (x == NIL) return;

    Print_Inorder(x->left);

    printf("%d ", x->key);

    Print_Inorder(x->right);

}

Node Search(Node now, int k)
{
    if (now == NIL || now->key == k) return now;

    if (k < now->key) return Search(now->left, k);

    else return Search(now->right, k);
}

Node Minimum(Node now)
{
    while (now->left != NIL) now = now->left;
    return now;
}

Node Maximum(Node now)
{
    while (now->right != NIL) now = now->right;
    return now;
}
/*
Node Successor(Node now, int x)
{
    Node temp = Search(now, x);

    if (temp == NIL)
    {
        printf("%d Doesn't Exist\n", x);
        return temp;
    }

    if (temp->right != NIL) return Minimum(temp->right);
    Node y = temp->p;

    while (y != NIL && temp == y->right)
    {
        temp = y;
        y = y->p;
    }
    return y;
}

Node Predecessor(Node now, int x)
{
    Node temp = Search(now, x);
    if (temp == NIL)
    {
        printf("%d Doesn't Exist\n", x);
        return temp;
    }

    if (temp->left != NIL) return Maximum(temp->left);

    Node y = temp->p;
    while (y != NIL && temp == y->left)
    {
        temp = y;
        y = y->p;
    }
    return y;
}
*/
void Left_Rotate(Node *root, Node x)
{
    Node y = x->right;
    x->right = y->left;

    if (y->left != NIL) y->left->p = x;
    y->p = x->p;

    if (x->p == NIL) *root = y;

    else if (x->p->left == x) x->p->left = y;

    else x->p->right = y;

    y->left = x;
    x->p = y;
}

void Right_Rotate(Node *root, Node y)
{
    Node x = y->left;
    y->left = x->right;

    if (x->right != NIL) x->right->p = y;
    x->p = y->p;
    if (y->p == NIL) *root = x;

    else if (y->p->left == y) y->p->left = x;

    else y->p->right = x;

    x->right = y;
    y->p = x;
}

void Insert_FixUp(Node *root, Node z)
{
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            Node y = z->p->p->right;            /// z's uncle
            if (y->color == RED)                /// case 1 : z's uncle y is red
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->right)           /// case 2 : z's uncle y is black & z is Right Child
                {
                    z = z->p;
                    Left_Rotate(root,z);
                }
                z->p->color = BLACK;            /// case 3 : z's uncle y is black & z is Left Child
                z->p->p->color = RED;
                Right_Rotate(root,z->p->p);
            }
        }
        else
        {
            Node y = z->p->p->left;

            if (y->color == RED)
            {
                z->p->color = y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;
                    Right_Rotate(root,z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                Left_Rotate(root,z->p->p);
            }
        }
    }
    (*root)->color = BLACK;
}

void Insert(Node *root, int z)
{
    Node Z = (Node) malloc(sizeof(struct Tree));

    Z->key = z;
    Node y = NIL , x = *root;

    while (x != NIL)
    {
        y = x;

        x = (z < x->key) ? x->left : x->right;
    }

    Z->p = y;

    if (y == NIL) *root = Z;

    else if (z < y->key) y->left = Z;

    else y->right = Z;

    Z->left = Z->right = NIL;
    Z->color = RED;
    Insert_FixUp(root,Z);
}

void Replace(Node *root, Node u, Node v)
{
    if (u->p == NIL)
        *root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    v->p = u->p;
}

void Delete_FixUp(Node *root, Node x)
{
    while (x != *root && x->color == BLACK)
    {
        if (x == x->p->left)
        {
            Node w = x->p->right;

            if (w->color == RED)                    /// Case 1 : x's Sibling w is red
            {
                w->color = BLACK;
                x->p->color = RED;
                Left_Rotate(root,x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {                   ///Case 2 : x's Sibling w is black both of w's childs black
                w->color = RED;
                x = x->p;
            }
            else
            {
                ///Case 3 : x's Sibling w,right child black , left child red
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    Right_Rotate(root,w);
                    w = x->p->right;
                }

                ///Case 4 : x's Sibling w,right child red , left child black
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                Left_Rotate(root,x->p);
                x = *root;
            }
        }
        else
        {
            Node w = x->p->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                Right_Rotate(root,x->p);
                w = x->p->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    Left_Rotate(root,w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                Right_Rotate(root,x->p);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

void Delete(Node *root, int z)
{
    Node x , Z = Search(*root, z);              /// Z: node to be deleted

    if (Z == NIL)return;

    Node y = Z;
    int y_org_color = y->color;                 ///   y: points to Z when Z has < 2 children and is deleted,
                                                /// otherwise, points to Z's successor and will move to Z's position

    if (Z->left == NIL)
    {
        x = Z->right;                           /// x: node that moves to y’s original position
        Replace(root,Z,Z->right);
    }
    else if (Z->right == NIL)
    {
        x = Z->left;
        Replace(root,Z,Z->left);
    }
    else
    {
        y = Minimum(Z->right);
        y_org_color = y->color;
        x = y->right;

        if (y->p == Z) x->p = y;
        else
        {
            Replace(root,y,y->right);
            y->right = Z->right;
            y->right->p = y;
        }
        Replace(root,Z,y);
        y->left = Z->left;
        y->left->p = y;
        y->color = Z->color;
    }

    if (y_org_color == BLACK) Delete_FixUp(root,x);
}

void init(){

    TNILL.left = TNILL.right = TNILL.p = NIL;
    TNILL.color = BLACK;
    tree = NIL;
}

int main()
{
    init();

    int n;

    while (1)
    {
        printf("1.Insert   2.Search  3.Print_Inorder  4.Delete   0.Exit\n\n");
        scanf("%d", &n);
        if (n == 1)
        {
            scn(n);
            Insert(&tree, n);
        }
        else if (n == 2)
        {
            scn(n);
            if (Search(tree, n) == NIL) cout<<"Not Found\n\n";
            else cout<<"Found\n";
        }
        else if (n == 3)
        {
            Print_Inorder(tree);
            printf("\n\n");
        }
        else if (n == 4)
        {
            scn(n);
            Delete(&tree, n);
        }
        else if(!n)break;
    }
    return 0;
}

/*
1 10
1 20
1 5
1 3
1 9
1 15
1 20
1 12
*/
