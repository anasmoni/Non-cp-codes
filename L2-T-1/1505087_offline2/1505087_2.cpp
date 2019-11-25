#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;
struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

struct listNode * New_Node(int item)
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = 0;
    return newNode;
}

struct listNode * searchItem(int item)
{
    struct listNode * temp ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) return temp ;
        temp = temp->next ; //move to next node
    }
    return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d -> ", temp->item);
        temp = temp->next;
    }
   // if(tail)printf("tail %d\n",tail->item);
    printf("\n");
}

int insertItem(int item) //insert at the beginning of the linked list
{
    struct listNode * newNode = New_Node(item) ;
    newNode->next = list ; //point to previous first node
    list = newNode ; //set list to point to newnode as this is now the first node
    if(tail==0)tail=list;
    return SUCCESS_VALUE ;
}

int insertBefore(int oldItem, int newItem)
{
    if(searchItem(oldItem)==0 || list->item==oldItem )insertItem(newItem);
    else
    {
        struct listNode * temp , *prev =NULL;
        temp = list ; //start at the beginning
        while (temp->item!= oldItem)
        {
            prev=temp;
            temp = temp->next ; //move to next node
        }
        struct listNode* nn = New_Node(newItem);
        prev->next = nn;
        nn->next = temp;
    }
    return SUCCESS_VALUE;
    //write your codes here
}

//add required codes to delete item, remember to properly set the tail pointer!

int deleteAfter(int item)
{
    struct listNode* nn = searchItem(item);
    if(nn==0)printf("Not found....\n");
    else
    {
        if(nn->next==0)return NULL_VALUE;
        else if(nn->next->next==0){nn->next=0;tail=nn;}
        else nn->next = nn->next->next;
    }
    return SUCCESS_VALUE;
}

int insertLast(int item)
{
    if(list==0)insertItem(item);
    else
    {
        tail->next = New_Node(item);
        tail = tail->next;
        tail->next=0;
    }
    return SUCCESS_VALUE;
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. InsertBefore. 2. DeleteAfter. 3. Search item. 7. InsertItem(first)\n");
        printf("4. InsertLast. 5. Print. 6. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item,n;
            scanf("%d%d",&n,&item);
            insertBefore(n,item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int i;
            scanf("%d",&i);
            insertLast(i);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==7)
        {
            int i;
            scanf("%d",&i);
            insertItem(i);
        }
        else if(ch==6)
        {
            break;
        }
    }

}
