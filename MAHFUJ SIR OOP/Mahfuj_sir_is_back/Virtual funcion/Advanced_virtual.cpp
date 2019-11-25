#include<bits/stdc++.h>
using namespace std;

class area{
    double dim1, dim2;
public:
    void set_dim(double d1,double d2){dim1 = d1 ; dim2 = d2;}
    void get_dim(double &d1 , double &d2){d1=dim1 ; d2=dim2;}
    virtual double get_area() = 0;
};

class rect:public area{
public:
    double get_area(){
        double d1,d2;
        get_dim(d1,d2);
        return d1*d2;
    }
};

class tri : public area{
public:
    double get_area(){
        double d1,d2;
        get_dim(d1,d2);
        return 0.5*d1*d2;
    }
};

int main()
{
    area *p;
    tri t;
    rect r;

    t.set_dim(5.0,10.0);
    r.set_dim(3.0,4.0);

    p=&t ; cout<<p->get_area()<<endl;
    p = &r ; cout<<p->get_area()<<endl;

    //p->set_dim(21,12); cout<<p->get_area(); // not allowed

    return 0;
}
