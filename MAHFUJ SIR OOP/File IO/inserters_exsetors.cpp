#include<bits/stdc++.h>
using namespace std;

class test1{
    int x,y;
public:
    test1(int a,int b){x=a;y=b;}
    friend ostream &operator<<(ostream &stream , test1 ob); // must be freind, inserter
    friend istream &operator>>(istream &stream,test1 &ob);// look -> &ob ;
        //without &(ob) line 40 will print 1 4
        // friend func's can be define here also

};

ostream &operator<<(ostream &stream , test1 ob){
    stream<<ob.x<<" "<<ob.y<<endl;
    stream<<"any operation will do!!"<<endl;
    return stream;
}

class test2{
public:
    int x,y;
    test2(int a,int b){x=a;y=b;}
    friend istream &operator>>(istream &stream, test2 &ob){
        stream>>ob.x>>ob.y;
        return stream;
    }
};

//EXERTOR
istream &operator>>(istream &stream,test1 &ob){ // look -> &ob ;
        //without &(ob) line 40 will print 1 4
        stream>>ob.x>>ob.y;
        return stream;
}
// INSERTER
ostream &operator<<(ostream &stream,test2 ob){
    stream<<ob.x+ob.y<<endl; // as x,y is public...we need not call friend inside class test2
    return stream;
}


int main()
{
    test1 a(1,4);
    test2 b(54,5);

    cout<<a<<b;
    cin>>a>>b;
    cout<<a<<b;


    return 0;
}
