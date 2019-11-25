/**If the object used as the arguments allocates dynamic memory
and free the memory then the destructor function is called
and the original object is damaged*/

#include<bits/stdc++.h>
#include<cstdlib>

using namespace std;

class dyna
{
    int *p;
public:
    dyna(int n);
    ~dyna();
    int get(){return *p;}
};

dyna::dyna(int n)
{
    p = new int[1];
    if(!p)cout<<"Allocation error..\n";
    else *p=n;
}

dyna::~dyna()
{
    free(p);
    cout<<"Freeing p.....\n";
}

int neg(dyna ob){return -ob.get();}

int srq_it(dyna *ob){return ob->get()*ob->get() ;}

dyna return_ob()
{
    dyna tob(3) ;
    cout<<"\nReturn object\n";
    return tob;

}


int main()
{
    dyna ob(5);

    cout<<"\nIt'tsrq_it(&ob)\n\n"<<endl;
    cout<<srq_it(&ob)<<endl;

    cout<<"\nIt's for ob.get()\n\n"<<endl;
    cout<<ob.get()<<endl;

    cout<<"\nIt's for neg(ob)\n\n"<<endl;
    cout<<neg(ob)<<endl;

    cout<<"\nIt's for ob.get()\n\n"<<endl;
    cout<<ob.get()<<endl;
    cout<<srq_it(&ob)<<endl;


    cout<<return_ob().get()<<endl;
    cout<<ob.get()<<endl;

    return 0;
}
