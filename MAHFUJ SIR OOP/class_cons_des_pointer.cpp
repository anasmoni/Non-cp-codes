#include<bits/stdc++.h>
using namespace std;

class strtype
{
    char  *p;
    int len;
public:
    ~strtype(){ cout<<"freeing p....\n" ; free(p);}

    strtype(char *ptr);

    void show(){cout<<p<<"\nLenght-"<<len<<endl;}
};

strtype::strtype(char *ptr)
{
    len = strlen(ptr);
    p = new char[len+1];  /** without this , the program will crash */
    if(!p)cout<<"Allocation error!\n";
    else strcpy(p,ptr);
}

int main()
{
    strtype ob1("This is a test!") , ob2("Hello World!");

    ob1.show();
    ob2.show();
    cout<<"\n\nAfter assigning with = sign\n\n";
    ob2 = ob1 ; /** as they are of same class*/
    ob2.show();

    return 0;
}
