#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
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

int insertFirst(int item) //insert at the beginning
{
	struct listNode * newNode = New_Node(item);

	if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
	return SUCCESS_VALUE ;
}


int deleteAfter(int i)
{
    struct listNode *temp = searchItem(i);

    if(temp==0 || temp->next==0)return NULL_VALUE;
    else{
        if(temp->next->next==0){temp->next=0;tail=temp;}
        else
        {
            struct listNode*dummy = temp->next->next;
            dummy->prev=temp;
            temp->next = dummy;
        }
    }
    return SUCCESS_VALUE;


}

int deleteLast()
{
    //write your codes here
    if(list==0){printf("Empty list....\n");return NULL_VALUE;}
    if(tail->prev==0){
            free(list);
            free(tail);
            initializeList();
            return NULL_VALUE;
    }
    tail->prev->next = 0;
    tail = tail->prev;

    return NULL_VALUE;
}




void printListForward()
{
    if(list==0){printf("Empty list");return;}
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d -> ", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

void printListBackward()
{
    if(list==0){printf("Empty list");return;}
    struct listNode*temp = tail;
    while(temp){
        printf("%d -> ",temp->item);
        temp = temp->prev;
    }
    printf("\n");
	//will print the list backward starting from the tail position
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. InsertFirst. 2. Delete_Last. 3. Search item. 7. DeleteAfter. \n");
        printf("4. Print forward. 5. Print backward. 6. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }
        else if(ch==2)
        {
            int item = deleteLast();
            if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
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
            printListForward();
        }
        else if(ch==5)
        {
            printListBackward();
        }
        else if(ch==7){
            int i;
            scanf("%d",&i);
            deleteAfter(i);
        }
        else if(ch==6)
        {
            break;
        }
    }

}
