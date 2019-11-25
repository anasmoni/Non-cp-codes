#include<bits/stdc++.h>
using namespace std;

class stop_watch{
    double en , beg;
public:
    stop_watch(){beg = en = 0.0;}
    stop_watch(clock_t t){
        beg = (double)t/CLOCKS_PER_SEC;
        en=0;
    }
    void start(){beg = (double)clock()/CLOCKS_PER_SEC;}
    void End(){en = (double)clock()/CLOCKS_PER_SEC;}
    void show(){cout<<en-beg<<endl;}
    ~stop_watch(){cout<<"Destroying......\n";}
};


int main(){

    stop_watch stp;
    stp.start();
    for(int i=0 ; i<100000000 ; i++);
    stp.End();
    stp.show();

    stop_watch s(clock());

    for(int i=0 ; i<1000000000 ; i++);

    s.End();
    s.show();

    return 0;
}
