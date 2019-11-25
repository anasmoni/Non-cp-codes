#include<bits/stdc++.h>
using namespace std;

class strtype
{
    char *p;
public:
    strtype(char *s);
    strtype(const strtype &ob);
    ~strtype(){delete [] p;}
    char *get(){return p;}
    //strtype &operator=(strtype &ob);
};

strtype::strtype(char *s)
{
    int l;
    l = strlen(s) + 1;
    p = new char[l];
    if (!p){cout << "Allocation error\n";  exit(1);}
    strcpy( p, s );
}

void show(strtype x){char *s;s=new char[1]; s = x.get();cout<<s<<endl;}

strtype::strtype(const strtype &ob)
{
    int l ; l = strlen((ob.p)) ; p=new char[1+l] ;
    if(!p)cout<<"Allocation Error\n";
    else strcpy(p,ob.p);

}

strtype strf(strtype &ob)
{
    strtype o("World");
    ob = o;
    return ob ;
}

int main()
{
    strtype ob("Hello");
    cout<<ob.get()<<endl;
    show(ob);
    cout<<ob.get()<<endl; /** garbage if we don't use copy constructor */
    show(ob);
    cout<<ob.get()<<"   "<<strf(ob).get()<<endl; /** so , no prblm */
    show(ob);
    show(strf(ob));

    return 0;
}
