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

void initializeList()
{
    list = 0;  //initially set to NULL
}

struct listNode * New_Node(int item)
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = 0;
    return newNode;
}

int insertItem(int item) //insert at the beginning of the linked list
{
    struct listNode * newNode = New_Node(item) ;
    newNode->next = list ; //point to previous first node
    list = newNode ; //set list to point to newnode as this is now the first node
    return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
    struct listNode *temp, *prev ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) break ;
        prev = temp;
        temp = temp->next ; //move to next node
    }
    if (temp == 0) return NULL_VALUE ; //item not found to delete
    if (temp == list) //delete the first node
    {
        list = list->next ;
        free(temp) ;
    }
    else
    {
        prev->next = temp->next ;
        free(temp);
    }
    return SUCCESS_VALUE ;
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
    if(list==0)
    {
        printf("Empty list\n");
        return;
    }
    while(temp!=0)
    {
        printf("%d -> ", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

int insertLast(int item)
{
    if(list==0)list = New_Node(item);
    else
    {
        struct listNode* temp = list;
        while(temp->next!=NULL)temp=temp->next;
        temp->next = New_Node(item);
    }
    return SUCCESS_VALUE;
    //write your codes here
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

int deleteAfter(int item)
{
    struct listNode* nn = searchItem(item);
    if(nn==0)printf("Not found....\n");
    else
    {
        if(nn->next==0)return NULL_VALUE;
        else if(nn->next->next==0)nn->next=0;
        else nn->next = nn->next->next;
    }
    return SUCCESS_VALUE;
}

int deleteLast()
{
    if(list==0)
    {
        printf("Empty list....\n");
        return NULL_VALUE;
    }
    struct listNode* nn = list;

    if(nn->next==0)initializeList();
    else {
        while(nn->next->next)nn=nn->next;
        nn->next=0;
    }

    return SUCCESS_VALUE;
}



int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. 7. InsertBefore. 8. DeleteAfter 9.DeleteLast \n");
        printf("4. InsertLast. 5. Print. 6. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
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
            scanf("%d", &i);
            insertLast(i);
        }
        else if(ch==7)
        {
            int o,n;
            scanf("%d%d", &o,&n);
            insertBefore(o,n);
        }
        else if(ch==8)
        {
            int o;
            scanf("%d", &o);
            deleteAfter(o);
        }
        else if(ch==9)deleteLast();
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }

    }

}
