/**A friend function can a member of a class and friend of another class */

#include<bits/stdc++.h>
using namespace std;

class truck;

class car
{
    int passengers;
    int speed;
public:
    car(int p, int s){passengers = p;speed = s;}
    int get(){return speed;}
    int sp_greater(truck t);
};

class truck
{
    int weight;
    int speed;
public:
    truck(int w, int s){ weight = w; speed = s;}
    friend int car::sp_greater(truck t);
};

int car::sp_greater(truck t){ return speed-t.speed ;}  /** look ... friend function is just like normal functions */

int main()
{
    car c(3,230);
    truck t(12,200);

    int d = c.sp_greater(t);

    if(d>0)cout<<"car!\n";
    else if(!d)cout<<"same!\n";
    else cout<<"Truck!\n";

    cout<<c.get();

    return 0;
}

