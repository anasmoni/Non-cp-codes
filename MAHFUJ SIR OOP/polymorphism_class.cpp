/** Function overloading , operator overloading */

#include<bits/stdc++.h>
using namespace std;

class date
{
    int day , month , year ;
public:
    date(char *str);
    date(int d,int m , int y){day=d , month=m , year=y  ;}
    void show(){cout<<day<<"/"<<month<<"/"<<year<<endl;}
};

date::date(char *str)
{
    sscanf(str,"%d%*c%d%*c%d",&day,&month,&year);
}



int main()
{
    date ob_str("12/2/2015") , ob_int(12,2,2015);

    ob_str.show();
    ob_int.show();


    return 0 ;
}
