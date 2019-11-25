#include<bits/stdc++.h>
using namespace std;

long mystrtol(char *s , char **End  , int base=10){
    return strtol(s,End,base);/** 2<=base<=38*/
}

int main()
{
    char *s = "1002453";
    long l;
    char *p;

    cout<<"For Base 16 -> "<<mystrtol(s,&p,16)<<endl;
    cout<<"For Base 8 -> "<<mystrtol(s,&p,8)<<endl;
    cout<<"For Default Base 10 -> "<<mystrtol(s,&p)<<endl;
    cout<<"What the hell *p is -> "<<*p; /** output nothing*/

    return 0;
}
