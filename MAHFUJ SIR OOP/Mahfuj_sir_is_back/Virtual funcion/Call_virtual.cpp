#include<bits/stdc++.h>
using namespace std;

class Father{
    char name[20];

public:

    Father(char *p){strcpy(name,p);}
    virtual void show(){cout<<name<<endl;} // virtual function should be in base class
};

class Son : public Father{
    char name[20];

public:

    Son(char *sname , char * fname):Father(fname){strcpy(name,sname);}
    void show(){cout<<name<<endl;}
};

int main()
{
    Father *f , father("Elias"), *p;
    Son s("Anas","Elias");

    f = &father;

    f->show(); // Elias

    f = &s;

    f->show(); // now..Anas
    f=p; // check

    return 0;
}


