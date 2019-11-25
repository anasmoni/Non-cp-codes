#include<bits/stdc++.h>
using namespace std;

class date{
    int month,year,day;
public:
    date(char *str){
        sscanf(str,"%d%*c%d%*c%d",&day,&month,&year);
    }

    date(int d ,int m , int y){
        day = d; month = m; year = y;
    }

    void show(){
        cout<<day<<'/'<<month<<'/'<<year<<endl;
    }
};


int main()
{
    date sdate("13/11/1997");
    date ndate(13,10,1997);
    sdate.show();
    ndate.show();



    return 0;
}
