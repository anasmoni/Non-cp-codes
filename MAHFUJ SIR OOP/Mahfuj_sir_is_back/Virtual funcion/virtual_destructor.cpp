#include<bits/stdc++.h>
using namespace std;

class Father{
    char *name;

public:

    Father(char *p){name = new char[strlen(p)+1] ; strcpy(name,p);}
    virtual void show(){cout<<name<<endl;} // virtual function should be in base class
    virtual ~Father(){delete name;  cout<<"Father destroyed\n";}
};

class Son : public Father{
    char *name;

public:

    Son(char *sname , char * fname):Father(fname){name = new char[strlen(sname)+1] ; strcpy(name,sname);}
    void show(){cout<<name<<endl;}
    ~Son(){delete name; cout<<"Son destroyed\n"; }
};

int main()
{
    Father *f , father("Elias");
    Son s("Anas","Elias");

    f = &father;

    f->show(); // Elias
    delete f;
    f = &s;

    f->show(); // now..Anas
    delete f;
    //f=p; // check

    return 0;
}



