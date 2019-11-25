/** when pointer is used -> operator is used rethar then . operator */
#include<bits/stdc++.h>
using namespace std;

class myclass
{
    int x;
public:
    myclass(int n){x=n ;}
    int getx(){return x;}
};


int main()
{
    myclass ob(5);
    myclass *p ;    /** pointer to object */
    p = &ob ; /** put address of ob into p*/

    cout<<"Get value using object : "<<ob.getx()<<endl;
    cout<<"Get value using pointer to object : "<<p->getx()<<endl;


    return 0;
}
