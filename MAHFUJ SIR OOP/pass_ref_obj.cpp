#include<bits/stdc++.h>
using namespace std;

class pass_ref
{
    int who;
public:
    pass_ref(int n){who=n ; cout<<"Constructing......\n";}
    int get(){return who;}
    ~pass_ref(){cout<<"\nDestructing.....\n";}
};

pass_ref f(pass_ref &ob)
{
    cout<<"Recieved : "<<ob.get()<<endl;
    return ob;
}

int x;
int &ret_ref(){return x;}

int main()
{
    pass_ref obj(5);
    cout<<f(obj).get();
    cout<<obj.get()<<endl;

    ret_ref() = 100 ;
    cout<<x<<endl;

    int m=10;
    int &independent_ref = m;
    m = 100;
    cout<<independent_ref<<" "<<m<<endl;

    m++; cout<<independent_ref<<endl;

    independent_ref=90;
    cout<<independent_ref<<" "<<m<<"  line 39 \n";
    independent_ref += 67;cout<<m<<endl;

    return 0;
}
