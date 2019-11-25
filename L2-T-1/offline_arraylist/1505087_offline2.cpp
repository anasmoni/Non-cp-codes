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

void clearList()
{
    delete(Arr_list);
    MAX_LEN = 2;
    Arr_list = new int[MAX_LEN];
    len=0;
}

void insertItem(int nelm)
{
    if(MAX_LEN == len)copy_all();

    Arr_list[len++] = nelm;
}

void deleteItem()
{
    --len;
    if(!len)clearList();
    else copy_all(false);
}

void Balanced_Bracket(string s){
    init();
    for(int i=0 ; s[i]; i++){
        if(s[i]=='{' || s[i]=='[' || s[i]=='(')insertItem(s[i]-'0');
        else{
            if(len==0){len=1;break;}
            if( abs((s[i]-'0') - Arr_list[len-1]) <= 2) deleteItem();

        }
    }
    if(len==0)cout<<"Balanced!\n";
    else cout<<"Not Balanced!\n";
    clearList();
}




int main()
{
    cout<<"Enter E to exit....\n";
    while(true){
        string s;
        cin>>s;
        if(s=="E")break;
        Balanced_Bracket(s);

    }
    return 0;
}
