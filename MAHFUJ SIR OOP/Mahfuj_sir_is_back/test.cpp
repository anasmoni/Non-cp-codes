 #include<iostream>
#include<typeinfo>
using namespace std;

class base{
    //...
    virtual void func(){};
};

class derrived1 : public base{
    //...
};

class new_derrived :public base{
    //...
};

void What_type(base &ob){
    cout<<typeid(ob).name()<<endl;
}

int main()
{
    int n;
    base *b,ob;
    derrived1 d1;
    new_derrived nd;
    cout<<typeid(n).name()<<endl;
    b = &ob;
    cout<<typeid(*b).name()<<endl;
    b = &d1;
    cout<<typeid(*b).name()<<endl;
    b = &nd;
    cout<<typeid(*b).name()<<endl;

    What_type(d1);
    What_type(nd);
    What_type(*b);


    return 0;
}
