#include<bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[])
{
    //if(argc!=2){cout<<"Balamar";return 0;}

    ofstream fout("output");
    ifstream fin("output");
    fin.unsetf(ios::skipws);

    while(!fin.eof())
    {
        char c;
        fin>>c;
        if(c==' ')c='|';
        cout<<c<<endl;
        if(!fin.eof())fout<<c;
    }
    fin.close();
    fout.close();
    return 0;
}
