/**A friend function is not a member of a class but still has access to
its private elements*/

#include<bits/stdc++.h>
using namespace std;

class truck;

class car
{
    int passengers;
    int speed;
public:
    car(int p, int s)
    {
        passengers = p;
        speed = s;
    }
    int get(){return speed;}

    friend int sp_greater(car c, truck t);
};

class truck
{
    int weight;
    int speed;
public:
    truck(int w, int s)
    {
        weight = w;
        speed = s;
    }
    friend int sp_greater(car c, truck t);
};

int sp_greater(car c , truck t){ return c.speed-t.speed ;}  /** look ... friend function is just like normal functions */

int main()
{
    car c(3,230);
    truck t(12,200);

    int d = sp_greater(c,t);

    if(d>0)cout<<"car!\n";
    else if(!d)cout<<"same!\n";
    else cout<<"Truck!\n";

    cout<<c.get();

    return 0;
}
