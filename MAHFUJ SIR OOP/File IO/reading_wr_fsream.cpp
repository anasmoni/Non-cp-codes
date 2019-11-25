#include<bits/stdc++.h>
using namespace std;

int main(){
    //ifstream fin("inp");
    /*ofstream fout("inp");
    fout<<"Hello world";
    fout.close();
    ifstream fin("inp");
    string s;
    //fin.unsetf(ios::skipws);
    int count_word=0;
    while(!fin.eof()){fin>>s;cout<<s<<" ";count_word++;} cout<<endl<<count_word<<endl;

    int cnt=0; char c;
    ifstream ifs("inp");
    while(!ifs.eof()){ifs>>c;cout<<endl<<c<<endl;if(c!=' ')cnt++; }
    cout<<endl<<cnt;

    fin.close();*/
    int n; scanf("%d",&n);
    int a[n],b[n];
    for(int t=0 ; t<n ;t++){scanf("%d",&a[t]);b[t]=a[t];}

    sort(b,b+n);

    int l=-1,h=-1,cnt=0;
    for(int i=0 ; i<n ; i++){
        if(a[i]!=b[i]){
            cnt++;
            if(l<0)l=i;
            else h=i;
        }
    }

    if(cnt==0){cout<<"yes";return 0;}
    else if(cnt==2){cout<<"yes\n"<<"swap "<<l+1<<" "<<h+1;return 0;}
    else{
        int k=l;cnt--;
        for( ;  a[l]>a[l+1] && cnt ; l++,cnt--);
        if(cnt==0){cout<<"yes\n"<<"reverse "<<k+1<<" "<<h+1;return 0;}
    }
    cout<<"no";


    return 0;
}
