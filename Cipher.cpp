#include<bits/stdc++.h>
#include <windows.h>
using namespace std;

typedef long long int lli;
typedef unsigned long long int ulli;
typedef pair<int,int> pii;

#define ones(x) __builtin_popcount(x)
#define onesl(x) __builtin_popcountl(x)
#define onesll(x) __builtin_popcountll(x)

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define scn(n) scanf("%d",&n)
#define scnll(n) scanf("%lld",&n)
#define scn2(n,m) scanf("%d%d",&n,&m)
#define scn3(n,m,w) scanf("%d%d%d",&n,&m,&w)
#define scn2ll(n,m) scanf("%lld%lld",&n,&m)
#define atoz(v) v.begin(),v.end()
#define ratoz(v) v.rbegin(),v.rend()
#define Fill(a,v) memset(a,v,sizeof(a))
#define sz(v) v.size()
#define fi first
#define se second
#define inf 1e9
#define pi acos(-1.0)
#define sqr(x) x*x
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define ten(n) (int)1e##n
#define tenll(n) (lli)1e##n
#define mod 1000000007
#define FastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int Set(int N,int pos)
{
    return N=N | (1<<pos);
}
int reset(int N,int pos)
{
    return N = N & ~(1<<pos);
}
bool check(int N,int pos)
{
    return (bool)(N & (1<<pos));
}
inline void MyAssert(bool ok){
    if(ok==false){
        cout<<"Your Assertion Failed";
        exit(0);
    }
}

string cipher ;
vector<char>mfc ; /// most frequent chars
vector<string>words ; /// words present in plain text
vector<pii>freq_cc; /// freq of cipher char
map<char,char>current_map; /// current mapping
map<char,char>mapping; /// best  mapping found so far

bool nonChar(char c){
    return !(c>='a' && c<='z');
}

void Init(){
    ifstream in;
    in.open("input.txt");
    in>>cipher;
    string s;

    while(in>>s){
        while(s.size() && nonChar(s.back()) ) s.pop_back();
        if(s.size()==0)continue;
        else if(s.size() == 1) mfc.pb(s[0]);
        else words.pb(s);
    }

    in.close();
}

void mfc_assign(){
    map<char,int>cnt;
    for(char c : cipher) cnt[c]++;
    vector<pii>v;
    for(char c='A'; c<='Z'; c++){
        if(cnt[c]==0)continue;
        v.pb({cnt[c],c-'A'});
    }
    sort(v.rbegin(), v.rend());
    while(v.size()){
        pii p = v.back();
        if(p.fi<v[mfc.size()-1].fi) v.pop_back();
        else break;
    }
    freq_cc = v;
}

bool isTaken(char X){
    for(auto it : current_map){
        if(it.se == X)return true;
    }
    return false;
}

bool isPossible(char c , char X){

    if(isTaken(X)) return false;
    /// does mfc info allow c to X mapping ?

    int idx = 0;

    for(char cc: mfc){

        if(cc == c){

            for(int i=idx; i<freq_cc.size(); i++){
                pii p = freq_cc[idx] , q = freq_cc[i];
                if(p.fi != q.fi) break;
                if(X-'A' == q.se) return true;
            }
            for(int i=idx; i>=0; i--){
                pii p = freq_cc[idx] , q = freq_cc[i];
                if(p.fi != q.fi) break;
                if(X-'A' == q.se) return true;
            }
            break;
        }

        idx++;
    }
    if(idx==mfc.size()) return true; /// c is not in max freq list...nothing to check
    return false;
}


void solve(int ith_Word){

    if(ith_Word == words.size()){
        if(current_map.size()>mapping.size()){
            mapping = current_map;
        }
        return;
    }
    map<char,char>prev;
    prev = current_map;

    for(int i=0,j,ii; (i+words[ith_Word].size()-1)<cipher.size(); i++){

        for(j=0,ii=i; j<words[ith_Word].size(); j++,ii++){

            char a = words[ith_Word][j] , X = cipher[ii];
            //cout<<j<<" "<<words[ith_Word].size()<<endl;
            if(current_map.find(a)==current_map.end()){
                if(isPossible(a,X)){
                    current_map[a] = X;

                }
                else break;
            }
            else if(current_map[a] != X)break;
        }
        if(j == words[ith_Word].size()) solve(ith_Word+1);
        current_map = prev;
    }
}

void Print_Plain_Text(string pt){

    vector<bool>color(pt.size()+3,false);

    for(int i=0; i<words.size(); i++){
        string w = words[i];
        bool ok = false;
        for(int j=0; (j+sz(w)-1)<pt.size(); j++){
            if(pt.substr(j,w.size()) == w){
                ok = true;
                for(int c=sz(w) ; c ; c--,j++) color[j] = true;
            }
        }
        MyAssert(ok);
    }

    for(int i=0; i<pt.size(); i++){
        if(color[i]){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        }
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout<<pt[i];
    }
    cout<<endl;
}

int main()
{
    Init(); /// taking input and parsing...
    mfc_assign();
    solve(0);

    map<char,char>Xtoa;

    for(auto it : mapping){
        Xtoa[it.se] = it.fi;
        //cout<<it.fi<<" "<<it.se<<endl;
    }
    cout<<"Plain Text :   ";
    string pt;
    for(char c : cipher){
        if(Xtoa.find(c) != Xtoa.end()) pt += Xtoa[c];
        else pt += c;
    }
    Print_Plain_Text(pt);

    //for(int i=0; i<freq_cc.size(); i++) cout<<(char)(freq_cc[i].se+'A')<<" ";

    return 0;

}
