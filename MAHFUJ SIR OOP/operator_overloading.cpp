#include<bits/stdc++.h>
using namespace std;

class cord
{
    int x,y;
public:

    cord(int i=0 , int j=0){x=i , y=j ;}
    void getxy(int &i , int &j){i=x,j=y;}
    cord operator+(cord ob);
    cord operator++();
    cord operator++(int notused=0){cord temp ; temp=*this ; x++,y++; return temp;}
    cord operator=(cord ob);
    //cord operator+(int i); ambegeous to line 22
    bool operator==(cord ob);
    cord operator-(cord ob); /** binary */
    cord operator-(); /** unary*/
    cord operator/(cord ob){cord temp ; temp.x = x/ob.x ; temp.y = y/ob.y ; return temp;}
    cord operator*(cord ob){cord temp; temp.x = x*ob.x ; temp.y = y*ob.y ; return temp;}
    bool operator<(cord ob){return (x<ob.x && y<ob.y);}
    friend cord operator+(int i,cord ob){cord temp; temp.x = i+ob.x; temp.y = i+ ob.y; return temp;}
    friend cord operator+(cord ob,int i){cord temp; temp.x = ob.x+i; temp.y = ob.y+i; return temp;}
    friend cord operator-(int i,cord ob){cord temp; temp.x = i-ob.x; temp.y = i- ob.y; return temp;}
    friend cord operator-(cord ob,int i){cord temp; temp.x = ob.x-i; temp.y = ob.y-i; return temp;}
    cord operator+=(int i){x+=i; y+=i; return *this;}
};

bool cord::operator==(cord ob){return x==ob.x && y==ob.y;}

cord cord::operator+(cord ob)
{
    x+=ob.x; y+=ob.y;
    return *this;
}

cord cord::operator++(){x++ ; y++ ; return *this;}

cord cord::operator=(cord ob){x = ob.x ; y = ob.y ; return *this; }

cord cord::operator-(){x=-x ; y=-y ; return *this;}

cord cord::operator-(cord ob){cord temp ; temp.x = x-ob.x ; temp.y = y-ob.y; return temp;}

int main()
{
    int i,j;

    cord ob1(3,4) , ob2(7,9) , ob3 ;

    ob1 = ob1+ob2; ob1.getxy(i,j); cout<<i<<" "<<j<<endl;

    ob3 = ob2/ob1 ;  ob3.getxy(i,j) ; cout<<i<<" "<<j<<endl;

    ob3 = ob2*ob1 ;  ob3.getxy(i,j) ; cout<<i<<" "<<j<<endl;

    ob1.getxy(i,j);  cout<<i<<" "<<j<<endl;

    ob1== ob2 ? cout<<"Same\n" : cout<<"Nope\n";

    ob3 = ob2 = ob1 ;
    ob1==ob3 ? cout<<"Same\n" : cout<<"Nope\n";


    //ob2++;   ob2.getxy(i,j);  cout<<i<<" "<<j<<endl;
    ob3 = ob3+ob2+ob1;  ob3.getxy(i,j);  cout<<"line -> 62   "<<i<<" "<<j<<endl;

    ++ob3; ob3.getxy(i,j) ; cout<<i<<" "<<j<<"    line  61\n";

    ob3++.getxy(i,j) ; cout<<i<<" "<<j<<"    line  65\n";
    ob3 = ++ob1; ob3.getxy(i,j) ; cout<<i<<" "<<j<<"    line  67\n";

    (ob1+ob3).getxy(i,j); cout<<i<<" "<<j<<endl;

    (ob1-ob3).getxy(i,j); cout<<i<<" "<<j<<"    line 66\n";

    ob3 = -ob3;
    ob3.getxy(i,j); cout<<i<<" "<<j<<endl;

    ob3  = 100 + ob3; ob3.getxy(i,j); cout<<"100+ob3 -> "<<i<<" "<<j<<endl;

    ob3  = ob3 + 5 ; ob3.getxy(i,j); cout<<"ob3+5 -> "<<i<<" "<<j<<endl;
    ob3  = ob3 - 5 ; ob3.getxy(i,j); cout<<"ob3-5 -> "<<i<<" "<<j<<endl;
    ob3  = 100-ob3 ; ob3.getxy(i,j); cout<<"100-ob3 -> "<<i<<" "<<j<<endl;
    ob1 = ob3;
    ob3 = ++ob1 + ob1++; ob3.getxy(i,j) ; cout<<"Line 86-> "<<i<<" "<<j<<endl;

    ob3 += 10; ob3.getxy(i,j) ; cout<<"Line 88-> "<<i<<" "<<j<<endl;

    ob3<ob1? cout<<"ob3<ob1\n" : cout<<"ob3>ob1\n" ;


    return 0;
}
