#include<bits/stdc++.h>
using namespace std;

ostream &setup(ostream &stream){
    stream.width(10);
    stream.fill('*');
    stream.precision(6);
    return stream;
}

ostream &atn(ostream &strm){
    strm<<"Attention ";
    return strm;
}

int main()
{
    cout<<setup << 123.215<<"    "<<setup<<" "<<14<<endl;
    cout<<atn<<"Check duration";
    cout<<'\a'; // sound bell

    return 0;
}
