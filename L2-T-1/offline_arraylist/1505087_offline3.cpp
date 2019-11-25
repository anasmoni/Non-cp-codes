#include<bits/stdc++.h>
using namespace std;

int *Arr_list , len , MAX_LEN = 2 ;

void init()
{
    Arr_list = new int[MAX_LEN];
}

void copy_all(bool change_MAX_LEN=true)
{
    int *t;

    if(change_MAX_LEN)MAX_LEN *= 2;

    t = new int[MAX_LEN];

    for(int i=0 ; i<len ; t[i]=Arr_list[i++]);

    delete(Arr_list);
    Arr_list = new int[MAX_LEN];
    Arr_list = t;
}

void print()
{
    for(int i=0 ; i<len ; cout<<Arr_list[i++]<<" ");
    cout<<endl;
}

void clearList()
{
    delete(Arr_list);
    MAX_LEN = 2;
    Arr_list = new int[MAX_LEN];
    len=0;
    cout<<"Clear Completed\n";
}

void insertItemAtPos(int elm , int pos)
{

    if(len==MAX_LEN)copy_all();

    for(int i=++len ; i>=pos ; Arr_list[i] = Arr_list[--i]);

    Arr_list[pos]=elm;
}

void insertItem(int nelm)
{

    if(MAX_LEN == len)copy_all();
    int i;

    for( i=0 ; i<len && Arr_list[i]<nelm ; i++);

    if(len==0)Arr_list[len++]=nelm;
    else insertItemAtPos(nelm,i);
    print();
}

void deleteFirstItem(int elm)
{
    int i=0;

    for( ; i<len && Arr_list[i]!=elm ; i++);

    if(i==len)
    {
        cout<<"Element Not Found\n";
        return;
    }
    else if(i==len-1){len--;copy_all();}
    else {for(--len; i<len ; Arr_list[i] = Arr_list[++i]);}
    if(!len)cout<<"Now list is empty";
    else print();
}

void searchItem(int val)
{
    int l=0,r=len-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(Arr_list[mid]==val){cout<<"Found At Position__"<<mid<<endl;return;}
        else if(val>mid)l=++mid;
        else r=--mid;
    }
    cout<<"Not Found\n";
}

void test()
{
    init();
    cout<<"Enter T to exit......\n";
    while(true)
    {
        char s,c;
        cin>>s;
        int j;
        if(s=='T'){cout<<"Exit...";return;}

        if(s=='I'){cin>>j; insertItem(j);}
        if(s=='D'){ cin>>j; deleteFirstItem(j); }

        if(s=='F'){cin>>j ; searchItem(j);}
        if(s=='C')clearList();

    }

}


int main()
{
    test();

    return 0;
}

