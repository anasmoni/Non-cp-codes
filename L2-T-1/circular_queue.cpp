#include<bits/stdc++.h>
using namespace std;
struct circullerqueue
{
    int a[10];
    int SIZE=0;
    int MAX_ELEMENT=10;
    int Front=-1,rear=-1;

    void push(int data)
    {
        if(Front==(rear+1)%MAX_ELEMENT)
        {
            cout<<"OVERFLOW"<<endl;
        }
        else
        {
            rear=(rear+1)%MAX_ELEMENT;
            a[rear]=data;
            if(Front==-1)
            {
                Front=0;
            }
        }

    }
    int pop()
    {
        if ((Front == rear) && (rear == -1))
        {
            cout<<"UNDERFLOW"<<endl;
        }
        else
        {
            int data=a[Front];
            if(Front==rear) Front=rear=-1;
            else
            {
                Front=(Front+1)%MAX_ELEMENT;
            }
            return data;
        }
    }
    void print()
    {
        if(Front==-1){
            cout<<"Circular queue is empty"<<endl;
            return ;
        }
        if(Front<=rear){
            for(int i=Front;i<=rear;i++){
                cout<<a[i]<<" ";
            }
        }
        else{
           for(int i=Front;i<MAX_ELEMENT;i++){
                cout<<a[i]<<" ";
            }
            for(int i=0;i<=rear;i++){
                cout<<a[i]<<" ";
            }
        }
        cout<<endl;
    }
};
int main()
{
    circullerqueue cqueue;
    for(int i=1; i<=5; i++){ cqueue.push(i);

    }
    cqueue.print();
    for(int i=1; i<=7; i++) {cqueue.pop();   // cout<<cqueue.Front<<" "<<cqueue.rear<<endl;
    }
    cqueue.print();
    //for(int i=0;i<10;i++) cout<<cqueue.a[i]<<" ";
     for(int i=11; i<=15; i++) {cqueue.push(i);
     // cout<<cqueue.Front<<" "<<cqueue.rear<<endl;
     }
    // for(int i=0;i<10;i++) cout<<cqueue.a[i]<<" ";
    cqueue.print();
}
