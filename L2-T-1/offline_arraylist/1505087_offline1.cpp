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

void insertItem(int nelm)
{

    if(MAX_LEN == len)copy_all();

    Arr_list[len++] = nelm;
    print();
}

void deleteItem()
{
    if(len==0)cout<<"empty list";
    else --len;

    print();
}

void insertItemAtPos(int elm , int pos)
{

    if(len==MAX_LEN)copy_all();

    for(int i=++len ; i>=pos ; Arr_list[i] = Arr_list[--i]);

    Arr_list[pos]=elm;
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
    print();
}

void deleteLastItem(int elm)
{
    int i;
    for(i=len-1 ; i>=0 && Arr_list[i]!=elm ; i--);

    if(i<0)cout<<"Element not found\n";
    else if(i==len-1){len--;copy_all();}
    else {for(; i<len ; Arr_list[i] = Arr_list[++i]);}
    if(!len)cout<<"Now list is empty";
    print();
}

void searchItem(int elm)
{
    int i;
    for(i=0 ; i<len && Arr_list[i]!=elm ; i++);
    if(i==len)
    {
        cout<<"Not Found\n";
        return;
    }
    cout<<"Found At Position__"<<i<<endl;
}

void test()
{
    init();
    cout<<"Enter T to terminate......\n";
    while(true)
    {
        char s;scanf("%c",&s);
        if(s=='T'){cout<<"Exit...";exit(0);}

        if(s=='I'){
            int i; cin>>i; char c[45]="$"; scanf("%[^\n]",c);
            if(c[0]=='$')insertItem(i);
            else insertItemAtPos(i,atoi(c));
        }
        if(s=='D')
        {
            int j;
            string c;getline(cin,c);
            if(c=="\0")deleteItem();
            else{
                char d=c[1];
                c = c.substr(2);
                j=atoi(c.c_str());
                if(d=='L') deleteLastItem(j);
                else deleteFirstItem(j);
            }
        }

        if(s=='S'){int j;cin>>j ; searchItem(j);}
        if(s=='C')clearList();
    }
}

int main()
{
    test();

    return 0;
}
