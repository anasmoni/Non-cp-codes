#include <iostream>
using namespace std;
class myclass
{
public:
    myclass();
    myclass(const myclass &o);
    //myclass f();
};

myclass::myclass()
{
    cout<<"Constructing normally\n";
}
myclass:: myclass(const myclass &o)
{
    cout<<"Constructing copy\n";
}
myclass f(myclass &b)
{
    return b;
}

int main()
{
    myclass obj;
    obj = f(obj);
    return 0;
}
