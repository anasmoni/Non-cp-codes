#include<bits/stdc++.h>
using namespace std;

class A{
public:
    virtual void print(){cout<<"Base class\n";}
};

class B : public A{
public:
    void print(){cout<<"Derrived\n";}
};

class C : public A{
public:
    void print(){cout<<"in class c\n";}
    void test(){cout<<"oka\n";}
};

int main(){
    A a,*p;
    p = &a;
    p->print();
    B b;
    p = &b;
    p->print();
    C c;
    p = &c;
    p->print();
    /** p->test(); error **/
    A *point;
    cout<<endl<<endl;

    for(int i=0 ; i<5 ; i++){
        int j =rand();
        if(j%2)point = &b;
        else point = &c;
        point->print();
    }

    return 0;
}
